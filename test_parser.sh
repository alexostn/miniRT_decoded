#!/bin/bash

# Script to test miniRT parser with different scene files

echo "=== miniRT Parser Test ==="
echo ""

# Array of test scenes
scenes=(
    "scenes/test_simple.rt"
    "scenes/valid_simple.rt"
    "scenes/test_parser_all.rt"
)

# Test each scene
for scene in "${scenes[@]}"; do
    if [ ! -f "$scene" ]; then
        echo "⚠️  Scene not found: $scene"
        continue
    fi
    
    echo "Testing: $scene"
    echo "---"
    
    # Run miniRT with timeout and capture output
    timeout 2s ./miniRT "$scene" 2>&1 &
    pid=$!
    
    # Wait a bit to see if it parses correctly
    sleep 0.5
    
    # Check if process is still running (means parsing succeeded)
    if kill -0 $pid 2>/dev/null; then
        echo "✅ Parser succeeded - window opened"
        kill $pid 2>/dev/null
    else
        wait $pid
        exit_code=$?
        if [ $exit_code -eq 0 ]; then
            echo "✅ Parser succeeded"
        else
            echo "❌ Parser failed with exit code: $exit_code"
        fi
    fi
    
    echo ""
done

echo "=== Invalid Scenes Test ==="
echo ""

# Test invalid scenes (should fail)
invalid_scenes=(
    "scenes/invalid_id.rt"
    "scenes/invalid_range_color.rt"
    "scenes/no_camera.rt"
    "scenes/no_ambient.rt"
)

for scene in "${invalid_scenes[@]}"; do
    if [ ! -f "$scene" ]; then
        echo "⚠️  Scene not found: $scene"
        continue
    fi
    
    echo "Testing: $scene (should fail)"
    echo "---"
    
    # Run and expect failure
    if ./miniRT "$scene" 2>&1 | grep -q "Error"; then
        echo "✅ Correctly detected as invalid"
    else
        echo "❌ Should have failed but didn't"
    fi
    
    echo ""
done

echo "=== Test Complete ==="
