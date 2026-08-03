# Fan curve control contract

MControlCenter uses the `BeardOverflow.msi_ec` D-Bus adaptor at `/msi_ec` for
fan control. The application never writes fan points through the legacy EC byte
interface. `msi_ec` is the authoritative control ABI; `ec_sys`/`acpi_ec` is an
optional, read-only source for legacy RPM diagnostics.

## Capability discovery

`getFanCurveCapability()` returns a structured `a{sv}` map:

- `supported`
- `threshold_count`, `level_count`
- `threshold_min`, `threshold_max`
- `level_min`, `level_max`
- `reason` when unsupported or incomplete

Editing is supported only when all values describe the verified 6-threshold,
7-level ABI (`0..100` thresholds and `0..150` raw EC fan levels) and all 26
CPU/GPU sysfs point files plus `fan_mode` are present and readable.

`getFanCurveProfile()` returns all 26 values whenever they are readable. The
`readable` field is independent of `valid`: out-of-range or badly ordered
values remain available so the editor can clamp them and repair the curve.
Ordering, ranges, and exact counts are validated strictly only when applying.

## Transaction

`applyFanCurveTransaction(a{sv} profile)` is synchronous and returns:

- `success`
- `effective_mode`
- `error`
- `rollback_status` (`not-needed`, `succeeded`, `failed_auto`, or
  `not-attempted`)

The helper validates exact counts/ranges, strict threshold ordering, and
nondecreasing levels. It snapshots the current mode and all 26 values, enters
`auto`, writes every point, reads every point back, and only then activates
`advanced`. Any failure first forces and verifies `auto`, restores and verifies
the snapshot, and restores the original mode. If an Advanced snapshot has an
invalid curve, its values are restored only under Auto and malformed Advanced
is never reactivated. If safety cannot be proved it forces Auto and reports
`failed_auto`.

Successful readback is the only condition under which the application persists
a firmware-bound verified profile. Legacy unscoped fan settings are not
replayed. Silent and Super Battery selections clear a stale Advanced
preference; only verified Balanced/Performance state may restore it after
startup or resume.

## Authorization and D-Bus

Before each mutating D-Bus call, the unprivileged client runs a bounded
(60-second) interactive `pkcheck` using its own unique system-bus name. The
privileged helper independently checks the actual incoming unique sender with a
short, noninteractive timeout and never displays an authentication dialog.
Direct/non-D-Bus helper calls are denied. The helper-side check remains
authoritative, and D-Bus calls use a timeout longer than that short check plus
the bounded transaction.

The arbitrary raw EC byte-write D-Bus method and Debug write control are not
available.
