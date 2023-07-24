import os
import sys
import asyncio
import threading
import shlex
import subprocess
import re

EXECUTABLE_NAME = "asp.c.exe"
CFLAGS = "-Wall -std=gnu2x -fcolor-diagnostics -fansi-escape-codes"

printlock = threading.Lock()

def is_older(file_a, file_b):
    if not os.path.exists(file_a) or not os.path.exists(file_b):
        return True

    mod_time_a = os.path.getmtime(file_a)
    mod_time_b = os.path.getmtime(file_b)
    return mod_time_a > mod_time_b

def needs_rebuild(file, obj, deps):
    if not os.path.exists(obj):
        return True

    if is_older(file, obj):
        return True

    for dep in deps:
        if is_older(dep, obj):
            return True

    return False

async def cc(in_c_file, out_obj_file):
    cmd = "clang -c %s %s -o %s" % (CFLAGS, in_c_file, out_obj_file)

    with printlock:
        print("CC   %s" % in_c_file)
    
    p = await asyncio.create_subprocess_exec(*shlex.split(cmd, posix=False), 
                                             stdout=subprocess.PIPE)
    if await p.wait() != 0:
        asyncio.get_running_loop().close()
        sys.exit(-1)

async def link(objs, exe_file):
    cmd = "clang %s %s -o %s" % (CFLAGS, " ".join(objs), exe_file)

    with printlock:
        print("LD   %s" % exe_file)

    p = await asyncio.create_subprocess_exec(*shlex.split(cmd, posix=False),
                                                 stdout=subprocess.PIPE)
        
    if await p.wait() != 0:
        asyncio.get_running_loop.close()
        sys.exit(-1)

async def get_cc_deps(in_c_file):
    deps = []

    cmd = "clang %s -M %s" % (CFLAGS, in_c_file)

    p = await asyncio.create_subprocess_exec(*shlex.split(cmd, posix=False), 
                                             stdout=subprocess.PIPE)
    stdout, _ = await p.communicate()

    stdout = stdout.decode().split(": ")[1]
 
    for include in stdout.split(" "):
        include = include.strip()
        
        if not os.path.exists(include) or len(include) <= 3:
            continue

        if os.path.isabs(include):
            include = os.path.relpath(include)

        if not os.path.isabs(include) and not include.startswith(".."):
            deps.append(include)

    return deps

def find_c_files(folder):
    c_files = []
    for root, _, files in os.walk(folder):
        for file in files:
            if file.endswith(".c"):
                c_files.append(os.path.join(root, file))

    return c_files

async def main():
    c_files = find_c_files(".")
    objs = []

    tasks = []
    semaphore = asyncio.Semaphore(12)

    needs_link = asyncio.Event()

    async def file_worker(file):
        try:
            async with semaphore:
                path_no_ext, _ = os.path.splitext(file)
                obj = "objs/" + re.sub(r"[<>:\"/\\|?*]", "_", path_no_ext[2:]) + ".o"
                objs.append(obj)

                deps = await get_cc_deps(file)

                if needs_rebuild(file, obj, deps):
                    needs_link.set()
                    await cc(file, obj)
        except:
           pass
    
    for file in c_files:
        task = asyncio.create_task(file_worker(file))
        tasks.append(task)

    await asyncio.gather(*tasks)

    if needs_link.is_set() or not os.path.exists(EXECUTABLE_NAME):
        await link(objs, EXECUTABLE_NAME)

if __name__ == "__main__":
    asyncio.run(main())
