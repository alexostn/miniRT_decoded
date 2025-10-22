# miniRT Documentation

## 📖 Start Here

**New to the project?** → Read [`DOCUMENTATION_SUMMARY.md`](DOCUMENTATION_SUMMARY.md)

This gives you an overview of all documentation and where to find what you need.

---

## 📁 Quick Navigation

### Essential Guides
- 🚀 [`QUICK_START.md`](QUICK_START.md) - Get started quickly
- 📋 [`DOCUMENTATION_SUMMARY.md`](DOCUMENTATION_SUMMARY.md) - Complete documentation index

### Core Modules
- 🔍 [`parser/`](parser/) - Parser architecture and validation
- 🎨 [`shapes-api.md`](shapes-api.md) - Object creation API
- 📐 [`geometry/`](geometry/) - Geometric shapes implementation

### Architecture & Performance
- ⚡ [`architecture-comparison.md`](architecture-comparison.md) - Architecture options
- 🧠 [`memory-management.md`](memory-management.md) - Memory & debugging
- 🚄 [`rendering-optimization.md`](rendering-optimization.md) - Performance tips

---

## 🎯 Common Tasks

### Testing Parser
```bash
# Read this first
cat docs/parser/PARSER_TESTING.md

# Run tests
./miniRT scenes/test_parser_all.rt
./test_parser.sh
```

### Understanding Validation
```bash
# Read validation rules
cat docs/parser/VALIDATION.md
```

### Creating Objects
```bash
# Learn the API
cat docs/shapes-api.md
```

---

## 📊 Documentation Structure

```
docs/
├── README.md                    ← You are here
├── DOCUMENTATION_SUMMARY.md     ← Overview of everything
├── QUICK_START.md               ← Quick start guide
│
├── parser/                      # Parser module
│   ├── README.md
│   ├── VALIDATION.md            # Validation rules
│   ├── PARSER_TESTING.md        # Testing guide
│   └── 01-06 diagrams           # Architecture diagrams
│
├── geometry/                    # Geometry module
│   └── ...
│
├── shapes-api.md                # Object creation API
├── architecture-comparison.md   # Architecture options
├── memory-management.md         # Debugging guide
└── rendering-optimization.md    # Performance guide
```

---

## ✅ Status

- ✅ Parser: All elements supported (A, C, L, sp, pl, cy)
- ✅ Validation: 16/16 tests passing
- ✅ Book tests: 327/327 passing (100%)
- ✅ Objects: Sphere, plane, cylinder complete
- ✅ API: Unified transformation-based architecture

---

**Need help?** Start with [`DOCUMENTATION_SUMMARY.md`](DOCUMENTATION_SUMMARY.md)
