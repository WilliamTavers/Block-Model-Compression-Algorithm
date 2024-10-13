import sys 
from collections import defaultdict

def parse_input():
    # Read the first line for dimensions
    first_line = sys.stdin.readline().strip()
    if not first_line:
        raise ValueError("First line is empty, expected dimensions.")
    dimensions = list(map(int, first_line.split(',')))
    if len(dimensions) != 6:
        raise ValueError("First line must contain 6 comma-separated integers.")
    x_count, y_count, z_count, parent_x, parent_y, parent_z = dimensions

    # Read the tag table
    tags = {}
    while True:
        line = sys.stdin.readline()
        if not line:
            break  # EOF reached
        line = line.strip()
        if not line:
            break  # Empty line indicates end of tag table
        if ',' not in line:
            continue  # Skip invalid lines
        tag, label = line.split(',', 1)
        tag = tag.strip()
        label = label.strip()
        tags[tag] = label

    # Read the block model
    block_model = []
    for z in range(z_count):
        slice_data = []
        for y in range(y_count):
            line = sys.stdin.readline()
            if not line:
                raise ValueError(f"Unexpected end of input while reading slice {z}, row {y}.")
            line = line.strip()
            if len(line) != x_count:
                raise ValueError(f"Line length {len(line)} does not match x_count {x_count}.")
            slice_data.append(line)
        block_model.append(slice_data)
        # Read the blank line between slices
        line = sys.stdin.readline()
        if not line:
            # If last slice, it's okay to not have a blank line
            if z < z_count - 1:
                raise ValueError(f"Expected blank line after slice {z}, but got EOF.")
        elif z < z_count - 1 and line.strip():
            raise ValueError(f"Expected blank line after slice {z}, but got: {line.strip()}")

    return x_count, y_count, z_count, parent_x, parent_y, parent_z, tags, block_model

def two_dimensional_rle(grid, z_value, parent_x, parent_y):
    rows = len(grid)
    cols = len(grid[0]) if rows > 0 else 0
    processed = [[False] * cols for _ in range(rows)]
    result = []

    for i in range(rows):
        for j in range(cols):
            if not processed[i][j]:  # Only process unprocessed cells
                current_label = grid[i][j]

                # Calculate horizontal run (xRunLength)
                x_run_length = 1
                while j + x_run_length < cols and grid[i][j + x_run_length] == current_label and x_run_length < parent_x:
                    x_run_length += 1

                # Calculate vertical run (yRunLength) for the entire x-run
                y_run_length = 1
                y_runs_match = True
                while i + y_run_length < rows and y_runs_match and y_run_length < parent_y:
                    for k in range(x_run_length):
                        if j + k >= cols or grid[i + y_run_length][j + k] != current_label:
                            y_runs_match = False
                            break
                    if y_runs_match:
                        if y_run_length < parent_y:
                            y_run_length += 1

                # Mark all cells in this block as processed
                for y in range(i, min(i + y_run_length, rows)):
                    for x in range(j, min(j + x_run_length, cols)):
                        processed[y][x] = True

                # Output the block: i,j,z_value,xRunLength,yRunLength,1,label
                result.append((i, j, z_value, x_run_length, y_run_length, 1, tags[current_label]))

    return result

# Main function to execute the program
if __name__ == "__main__":
    x_count, y_count, z_count, parent_x, parent_y, parent_z, tags, grid = parse_input()
    rle_result = []

    for z in range(z_count):
        rle_result.extend(two_dimensional_rle(grid[z], z, parent_x, parent_y))

    # Print the results
    for block in rle_result:
        i, j, z, x_run_length, y_run_length, count, label_name = block
        print(','.join(map(str, block)))
