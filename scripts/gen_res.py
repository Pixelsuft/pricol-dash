import os


__cwd = os.path.dirname(__file__)
cwd = os.path.dirname(__cwd) if __cwd.strip() else os.getcwd()

ld = os.listdir(os.path.join(cwd, 'assets'))

png_files = []
mp3_files = []
ogg_files = []
fnt_files = []
sheet_files = []
plist_files = []

for i in ld:
    if '-hd' in i:
        continue
    fp = os.path.join(cwd, 'assets', i)
    if i.endswith('.png'):
        png_files.append(i)
        continue
    if i.endswith('.mp3'):
        mp3_files.append(i)
        continue
    if i.endswith('.ogg'):
        ogg_files.append(i)
        continue
    if i.endswith('.fnt'):
        fnt_files.append(i)
        continue
    if i.endswith('.plist'):
        data = open(fp, 'r', encoding='utf-8').read()
        if '.png</key>' in data:
            sheet_files.append(i)
            for j in data.replace('</key>', '<key>').split('<key>'):
                if j.endswith('.png'):
                    png_files.append(j)
        else:
            plist_files.append(i)
        continue

def write_map_for(id_str: str, val: any) -> None:
    mx_len = max([len(x) for x in val]) + 1
    f.write(f'static int get_{id_str}_id(const char* file_name)')
    f.write(' {\n   if (0) return -1;\n')
    for n, i in enumerate(val):
        f.write(f'   else if (STRNEQ(file_name, "{i}", {mx_len})) return {n};\n')
    f.write('   else return -1;\n}\n\n')
    f.write(f'#define RES_{id_str.upper()}(file_name) get_{id_str}_id(file_name)\n')
    f.write(f'#define MAX_RES_{id_str.upper()} {len(val)}\n')

f = open(os.path.join(cwd, 'include', 'gen', 'res_map.h'), 'w', encoding='utf-8')
f.write('#pragma once\n#include <app/base.h>\n')
f.write('#include <app/sdl2.h>\n\n')
write_map_for('png', png_files)
f.write('\n')
write_map_for('mp3', mp3_files)
f.write('\n')
write_map_for('ogg', ogg_files)
f.write('\n')
write_map_for('fnt', fnt_files)
f.write('\n')
write_map_for('sheet', sheet_files)
f.write('\n')
write_map_for('plist', plist_files)
f.close()
