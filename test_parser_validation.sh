#!/bin/bash

# miniRT Parser Test Suite
# Tests all validation scenarios

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0

echo "========================================"
echo "  miniRT Parser Validation Test Suite"
echo "========================================"
echo ""

# Function to test a valid scene (should render/timeout)
test_valid() {
    local file=$1
    local description=$2
    
    echo -n "Testing: $description ... "
    timeout 1 ./miniRT "$file" >/dev/null 2>&1
    exit_code=$?
    
    # Exit code 124 means timeout (rendering started = success)
    # Exit code 0 means program exited cleanly (also OK for some cases)
    if [ $exit_code -eq 124 ] || [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL (exit code: $exit_code)${NC}"
        ((FAILED++))
    fi
}

# Function to test an invalid scene (should output "Error\n")
test_invalid() {
    local file=$1
    local description=$2
    
    echo -n "Testing: $description ... "
    output=$(./miniRT "$file" 2>&1 | head -1)
    
    if [ "$output" = "Error" ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo "  Expected: 'Error'"
        echo "  Got: '$output'"
        ((FAILED++))
    fi
}

echo "=== VALID SCENES ==="
test_valid "scenes/valid_simple.rt" "Simple valid scene"
test_valid "scenes/test_negative.rt" "Scene with negative coordinates"

echo ""
echo "=== INVALID SCENES ==="
test_invalid "scenes/invalid_no_light.rt" "Missing required light (L)"
test_invalid "scenes/invalid_letter_in_number.rt" "Letter in number (12.a)"
test_invalid "scenes/invalid_incomplete_color.rt" "Incomplete RGB color"
test_invalid "scenes/invalid_missing_sphere_color.rt" "Missing sphere color"
test_invalid "scenes/invalid_range_color.rt" "RGB out of range [0-255]"
test_invalid "scenes/invalid_range_fov.rt" "FOV out of range [0-180]"
test_invalid "scenes/invalid_range_ambient.rt" "Ambient out of range [0-1]"
test_invalid "scenes/no_ambient.rt" "Missing ambient light (A)"
test_invalid "scenes/no_camera.rt" "Missing camera (C)"
test_invalid "scenes/invalid_id.rt" "Invalid identifier"
test_invalid "scenes/invalid_argc_extra.rt" "Extra arguments"
test_invalid "scenes/invalid_argc_missing.rt" "Missing arguments"
test_invalid "scenes/invalid_format_letter.rt" "Invalid format (letter)"
test_invalid "scenes/invalid_format_color.rt" "Invalid color format"

echo ""
echo "========================================"
echo "           TEST SUMMARY"
echo "========================================"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"
echo "Total:  $((PASSED + FAILED))"
echo ""

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}✓ All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}✗ Some tests failed${NC}"
    exit 1
fi
