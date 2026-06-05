import os
import subprocess
import sys

from SCons.Script import DefaultEnvironment


def merge_post_action(source, target, env):
    build_dir = env.subst("$BUILD_DIR")
    bootloader = os.path.join(build_dir, "bootloader.bin")
    partitions = os.path.join(build_dir, "partitions.bin")
    firmware = os.path.join(build_dir, "firmware.bin")
    merged = os.path.join(build_dir, "merged-firmware.bin")
    padding = os.path.join(build_dir, "padding.bin")

    with open(padding, "wb") as f:
        f.write(b"\x00" * 0x1000)

    python_exe = env.subst("$PYTHONEXE") or sys.executable
    esptool_pkg_dir = os.path.expanduser("~/.platformio/packages/tool-esptoolpy")
    if not os.path.isdir(esptool_pkg_dir):
        raise FileNotFoundError(f"esptool package directory was not found: {esptool_pkg_dir}")

    cmd = [
        python_exe,
        "-m",
        "esptool",
        "--chip",
        "esp32",
        "merge_bin",
        "--output",
        merged,
        "--flash_mode",
        "dout",
        "--flash_freq",
        "40m",
        "--flash_size",
        "4MB",
        "0x0",
        padding,
        "0x1000",
        bootloader,
        "0x8000",
        partitions,
        "0x10000",
        firmware,
    ]

    print(
        "\n[post] Generating merged-firmware.bin from bootloader.bin, partitions.bin, firmware.bin"
    )
    env_vars = os.environ.copy()
    env_vars["PYTHONPATH"] = esptool_pkg_dir
    result = subprocess.run(cmd, cwd=build_dir, env=env_vars)
    if result.returncode != 0:
        print("[post] merge_bin failed", file=sys.stderr)
        return result.returncode

    print(f"[post] Created: {merged}")
    return None


def add_merge_action(env):
    env.AddPostAction(
        "$BUILD_DIR/firmware.bin",
        env.Action(merge_post_action, "Merging firmware binaries into merged-firmware.bin...")
    )


env = DefaultEnvironment()
add_merge_action(env)
