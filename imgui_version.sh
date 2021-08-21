git ls-remote --tags https://github.com/ocornut/imgui | grep -o 'v\([0-9]\|\.\)*' | sort -r | sed -n 1p
