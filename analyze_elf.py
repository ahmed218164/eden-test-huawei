#!/usr/bin/env python3
"""
ELF Dependency Analyzer
Extracts NEEDED libraries from an ELF shared object file
"""

import struct
import sys

def read_elf_dependencies(filepath):
    """Read NEEDED dependencies from an ELF file"""
    
    with open(filepath, 'rb') as f:
        # Read ELF header
        elf_header = f.read(64)
        
        # Check ELF magic
        if elf_header[:4] != b'\x7fELF':
            print("Error: Not a valid ELF file")
            return []
        
        # Get ELF class (32-bit or 64-bit)
        elf_class = elf_header[4]
        is_64bit = (elf_class == 2)
        
        # Get endianness
        endian = elf_header[5]
        is_little_endian = (endian == 1)
        endian_char = '<' if is_little_endian else '>'
        
        if is_64bit:
            # 64-bit ELF
            # Program header offset at 0x20
            ph_offset = struct.unpack(endian_char + 'Q', elf_header[32:40])[0]
            # Section header offset at 0x28
            sh_offset = struct.unpack(endian_char + 'Q', elf_header[40:48])[0]
            # Program header entry size at 0x36
            ph_entsize = struct.unpack(endian_char + 'H', elf_header[54:56])[0]
            # Program header count at 0x38
            ph_num = struct.unpack(endian_char + 'H', elf_header[56:58])[0]
            # Section header entry size at 0x3A
            sh_entsize = struct.unpack(endian_char + 'H', elf_header[58:60])[0]
            # Section header count at 0x3C
            sh_num = struct.unpack(endian_char + 'H', elf_header[60:62])[0]
        else:
            # 32-bit ELF
            ph_offset = struct.unpack(endian_char + 'I', elf_header[28:32])[0]
            sh_offset = struct.unpack(endian_char + 'I', elf_header[32:36])[0]
            ph_entsize = struct.unpack(endian_char + 'H', elf_header[42:44])[0]
            ph_num = struct.unpack(endian_char + 'H', elf_header[44:46])[0]
            sh_entsize = struct.unpack(endian_char + 'H', elf_header[46:48])[0]
            sh_num = struct.unpack(endian_char + 'H', elf_header[48:50])[0]
        
        # Find DYNAMIC segment
        dynamic_offset = None
        dynamic_size = None
        
        for i in range(ph_num):
            f.seek(ph_offset + i * ph_entsize)
            ph_entry = f.read(ph_entsize)
            
            if is_64bit:
                p_type = struct.unpack(endian_char + 'I', ph_entry[0:4])[0]
                p_offset = struct.unpack(endian_char + 'Q', ph_entry[8:16])[0]
                p_filesz = struct.unpack(endian_char + 'Q', ph_entry[32:40])[0]
            else:
                p_type = struct.unpack(endian_char + 'I', ph_entry[0:4])[0]
                p_offset = struct.unpack(endian_char + 'I', ph_entry[4:8])[0]
                p_filesz = struct.unpack(endian_char + 'I', ph_entry[16:20])[0]
            
            # PT_DYNAMIC = 2
            if p_type == 2:
                dynamic_offset = p_offset
                dynamic_size = p_filesz
                break
        
        if dynamic_offset is None:
            print("Error: No DYNAMIC segment found")
            return []
        
        # Find string table (STRTAB)
        f.seek(dynamic_offset)
        dynamic_data = f.read(dynamic_size)
        
        strtab_offset = None
        needed_offsets = []
        
        entry_size = 16 if is_64bit else 8
        num_entries = dynamic_size // entry_size
        
        for i in range(num_entries):
            offset = i * entry_size
            if is_64bit:
                d_tag = struct.unpack(endian_char + 'Q', dynamic_data[offset:offset+8])[0]
                d_val = struct.unpack(endian_char + 'Q', dynamic_data[offset+8:offset+16])[0]
            else:
                d_tag = struct.unpack(endian_char + 'I', dynamic_data[offset:offset+4])[0]
                d_val = struct.unpack(endian_char + 'I', dynamic_data[offset+4:offset+8])[0]
            
            # DT_STRTAB = 5
            if d_tag == 5:
                strtab_offset = d_val
            # DT_NEEDED = 1
            elif d_tag == 1:
                needed_offsets.append(d_val)
            # DT_NULL = 0 (end of dynamic section)
            elif d_tag == 0:
                break
        
        if strtab_offset is None:
            print("Error: No STRTAB found")
            return []
        
        # Find the actual file offset of STRTAB
        strtab_file_offset = None
        for i in range(ph_num):
            f.seek(ph_offset + i * ph_entsize)
            ph_entry = f.read(ph_entsize)
            
            if is_64bit:
                p_type = struct.unpack(endian_char + 'I', ph_entry[0:4])[0]
                p_offset = struct.unpack(endian_char + 'Q', ph_entry[8:16])[0]
                p_vaddr = struct.unpack(endian_char + 'Q', ph_entry[16:24])[0]
                p_filesz = struct.unpack(endian_char + 'Q', ph_entry[32:40])[0]
            else:
                p_type = struct.unpack(endian_char + 'I', ph_entry[0:4])[0]
                p_offset = struct.unpack(endian_char + 'I', ph_entry[4:8])[0]
                p_vaddr = struct.unpack(endian_char + 'I', ph_entry[8:12])[0]
                p_filesz = struct.unpack(endian_char + 'I', ph_entry[16:20])[0]
            
            # PT_LOAD = 1
            if p_type == 1:
                if p_vaddr <= strtab_offset < p_vaddr + p_filesz:
                    strtab_file_offset = p_offset + (strtab_offset - p_vaddr)
                    break
        
        if strtab_file_offset is None:
            print("Error: Could not find STRTAB file offset")
            return []
        
        # Read library names
        dependencies = []
        for str_offset in needed_offsets:
            f.seek(strtab_file_offset + str_offset)
            lib_name = b''
            while True:
                char = f.read(1)
                if char == b'\x00' or not char:
                    break
                lib_name += char
            dependencies.append(lib_name.decode('utf-8'))
        
        return dependencies

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python analyze_elf.py <path_to_so_file>")
        sys.exit(1)
    
    filepath = sys.argv[1]
    
    print(f"Analyzing: {filepath}")
    print("=" * 70)
    
    dependencies = read_elf_dependencies(filepath)
    
    if dependencies:
        print(f"\nFound {len(dependencies)} NEEDED libraries:\n")
        for i, lib in enumerate(dependencies, 1):
            print(f"  {i}. {lib}")
    else:
        print("\nNo dependencies found or error occurred.")
