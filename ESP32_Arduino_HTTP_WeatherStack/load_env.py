# PlatformIO pre-script: reads .env and injects each KEY=VALUE as a C string macro.
Import("env")
import os

env_path = os.path.join(env["PROJECT_DIR"], ".env")
if not os.path.isfile(env_path):
    raise SystemExit("Missing .env file: copy .env.example to .env and set your values.")

with open(env_path, encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        value = value.strip().strip('"').strip("'")
        env.Append(CPPDEFINES=[(key.strip(), env.StringifyMacro(value))])
