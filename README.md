# Fixed-Point Kalman Filter in C

A Kalman filter implementation in pure C using fixed-point arithmetic. Designed to work on platforms with or without 128-bit integer support.

## Project Structure

```
├── include/
│   ├── fp_arithmetic.h   # Fixed-point arithmetic (Q32.32 / Q16.16)
│   ├── matrix.h          # Linear matrix API
│   ├── object.h          # Kinematic state representation
│   ├── assert_test.h     # Test assertion macros
│   ├── log.h             # Logging macros
│   └── other.h           # Common types and error codes
├── src/
│   ├── matrix.c          # Matrix operations implementation
│   └── object.c          # State ↔ matrix conversions
├── tests/
│   ├── matrix_test.c     # Matrix unit tests
│   └── object_test.c     # Object unit tests
├── scripts/
│   └── vis.py            # Visualization helper
├── main.c
└── Makefile
```

## Fixed-Point Arithmetic

The numeric type adapts to the target platform at compile time:
```
┌────────────────────────────────────────────────────────────────────────────┐
| Platform capability  | Type      | Format | Integer bits | Fractional bits |
|----------------------|-----------|--------|--------------|-----------------|
| `__int128` supported | `int64_t` | Q32.32 | 32           | 32              |
|----------------------------------------------------------------------------|
| No 128-bit integers  | `int32_t` | Q16.16 | 16           | 16              |
└────────────────────────────────────────────────────────────────────────────┘
```

Multiplication and division widen to the extended type internally to prevent overflow.

## Matrix Library

Matrices are stored as contiguous 1D arrays (row-major) for cache-friendly access. Supported operations:

- Init / destroy / copy
- Identity, fill, random
- Element access (`matrix_at`, `matrix_put`)
- Negate, scale, add
- Dot product (matrix multiply)
- Transpose
- Determinant (2x2, 3x3)
- Inverse (2x2, 3x3)

## State Representation

Kinematic state per dimension is a 3x1 column vector:

```
┌──────────────┐
│   position   │
│   velocity   │
│ acceleration │
└──────────────┘
```

Multi-dimensional objects use a 3×N matrix where each column is one spatial dimension.

## Building

```bash
make            # build bin/program
make test       # build and run all tests
make clean      # remove build artifacts
make format     # format source files with clang-format
```

Requires `gcc` and optionally `clang-format`.

## License

MIT License — see source file headers for details.
