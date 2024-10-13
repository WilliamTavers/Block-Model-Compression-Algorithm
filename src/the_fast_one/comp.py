def parse_input():
    first_line = input().strip().split(',')
    x_count, y_count, z_count = map(int, first_line[:3])
    parent_x, parent_y, parent_z = map(int, first_line[3:])
    
    tag_table = {}
    while True:
        line = input().strip()
        if line == "":
            break
        tag, label = line.split(',')
        tag_table[tag] = label
    
    block_model = []
    for z in range(z_count):
        slice_data = []
        for y in range(y_count):
            slice_data.append(input().strip())
        block_model.append(slice_data)
        if z != z_count - 1:
            input().strip()  
    
    return x_count, y_count, z_count, parent_x, parent_y, parent_z, tag_table, block_model

def compress_block_model(x_count, y_count, z_count, block_model, tag_table):
    compressed_blocks = []
    processed = [[[False for _ in range(x_count)] for _ in range(y_count)] for _ in range(z_count)]
    for z in range(0, z_count, 2):
        for y in range(0, y_count, 2):
            for x in range(0, x_count, 2):
                if not all_within_bounds(x, y, z, x_count, y_count, z_count):
                    continue
                if not try_compress_2x2x2_block(x, y, z, block_model, compressed_blocks, tag_table, processed):
                    if not try_compress_2x2x1_block(x, y, z, block_model, compressed_blocks, tag_table, processed):
                        if not try_compress_2x1x1_block(x, y, z, block_model, compressed_blocks, tag_table, processed):
                            compress_individual_blocks(x, y, z, block_model, compressed_blocks, tag_table, processed, x_count, y_count, z_count)
                        if not try_compress_2x1x1_block(x, y + 1, z, block_model, compressed_blocks, tag_table, processed):
                            compress_individual_blocks(x, y + 1, z, block_model, compressed_blocks, tag_table, processed, x_count, y_count, z_count)
                    if not try_compress_2x2x1_block(x, y, z + 1, block_model, compressed_blocks, tag_table, processed):
                        if not try_compress_2x1x1_block(x, y, z + 1, block_model, compressed_blocks, tag_table, processed):
                            compress_individual_blocks(x, y, z + 1, block_model, compressed_blocks, tag_table, processed, x_count, y_count, z_count)
                        if not try_compress_2x1x1_block(x, y + 1, z + 1, block_model, compressed_blocks, tag_table, processed):
                            compress_individual_blocks(x, y + 1, z + 1, block_model, compressed_blocks, tag_table, processed, x_count, y_count, z_count)
    
    # Final pass: Compress any remaining unprocessed blocks as 1x1x1
    for z in range(z_count):
        for y in range(y_count):
            for x in range(x_count):
                if not processed[z][y][x]:
                    tag = block_model[z][y][x]
                    label = tag_table.get(tag, 'UNKNOWN')
                    compressed_blocks.append((x, y, z, 1, 1, 1, label))
                    processed[z][y][x] = True

    return compressed_blocks

def try_compress_2x1x1_block(start_x, start_y, start_z, block_model, compressed_blocks, tag_table, processed):
    """ Try to compress a 2x1x1 block (two columns and one row in the x, y, z plane) """
    first_tag = block_model[start_z][start_y][start_x]

    for x_offset in range(2):
        if processed[start_z][start_y][start_x + x_offset]:
            return False
        if block_model[start_z][start_y][start_x + x_offset] != first_tag:
            return False

    label = tag_table.get(first_tag, 'UNKNOWN')
    compressed_blocks.append((start_x, start_y, start_z, 2, 1, 1, label))

    for x_offset in range(2):
        processed[start_z][start_y][start_x + x_offset] = True

    return True

def all_within_bounds(x, y, z, x_count, y_count, z_count):
    return x + 1 < x_count and y + 1 < y_count and z + 1 < z_count

def try_compress_2x2x2_block(start_x, start_y, start_z, block_model, compressed_blocks, tag_table, processed):
    """ just for testing """
    first_tag = block_model[start_z][start_y][start_x]

    # Check if all blocks in the 2x2x2 region are the same and unprocessed
    for z_offset in range(2):
        for y_offset in range(2):
            for x_offset in range(2):
                if processed[start_z + z_offset][start_y + y_offset][start_x + x_offset]:
                    return False
                if block_model[start_z + z_offset][start_y + y_offset][start_x + x_offset] != first_tag:
                    return False

    # Compress the 2x2x2 block
    label = tag_table.get(first_tag, 'UNKNOWN')
    compressed_blocks.append((start_x, start_y, start_z, 2, 2, 2, label))

    # Mark the blocks as processed
    for z_offset in range(2):
        for y_offset in range(2):
            for x_offset in range(2):
                processed[start_z + z_offset][start_y + y_offset][start_x + x_offset] = True

    return True

def try_compress_2x2x1_block(start_x, start_y, start_z, block_model, compressed_blocks, tag_table, processed):
    first_tag = block_model[start_z][start_y][start_x]
    
    for y_offset in range(2):
        for x_offset in range(2):
            if processed[start_z][start_y + y_offset][start_x + x_offset]:
                return False
            if block_model[start_z][start_y + y_offset][start_x + x_offset] != first_tag:
                return False
    

    label = tag_table.get(first_tag, 'UNKNOWN')
    compressed_blocks.append((start_x, start_y, start_z, 2, 2, 1, label))
    
    for y_offset in range(2):
        for x_offset in range(2):
            processed[start_z][start_y + y_offset][start_x + x_offset] = True
    
    return True


def compress_individual_blocks(start_x, start_y, start_z, block_model, compressed_blocks, tag_table, processed, x_count, y_count, z_count):
    """Compress individual blocks in the block_model. Handles up to a 2x2 area with a depth that can be set (default 2 for full 2x2x2).
       If depth=1, only processes a 2x2x1 area."""
    for z_offset in range(1):  
        for y_offset in range(1):
            for x_offset in range(2):
                if start_x + x_offset < x_count and start_y + y_offset < y_count and start_z + z_offset < z_count:
                    if not processed[start_z + z_offset][start_y + y_offset][start_x + x_offset]:
                        tag = block_model[start_z + z_offset][start_y + y_offset][start_x + x_offset]
                        label = tag_table.get(tag, 'UNKNOWN')
                        compressed_blocks.append((start_x + x_offset, start_y + y_offset, start_z + z_offset, 1, 1, 1, label))
                        processed[start_z + z_offset][start_y + y_offset][start_x + x_offset] = True


def output_compressed_blocks(compressed_blocks):
    for block in compressed_blocks:
        print(f"{block[0]},{block[1]},{block[2]},{block[3]},{block[4]},{block[5]},{block[6]}")

def main():
    x_count, y_count, z_count, parent_x, parent_y, parent_z, tag_table, block_model = parse_input()
    
    compressed_blocks = compress_block_model(x_count, y_count, z_count, block_model, tag_table)
    
    output_compressed_blocks(compressed_blocks)

if __name__ == "__main__":
    main()
