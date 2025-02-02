def generate_cpp(macros: dict[str, str]):
    out: str = ''

    for idx, (macro, value) in enumerate(macros.items()):
        out += f'\t\tconstexpr const telemetry_channel {macro} = "{value}";\n\n'
        out += f'\t\tconstexpr const telemetry_id ID_{macro} = {idx};\n\n'

    out += '\t\tconstexpr const telemetry_channel MAPPINGS[] = {\n'
    for idx, value in enumerate(macros.values()):
        out += f'\t\t\t"{value}"'
        if idx != len(macros) - 1:
            out += ','
        out += '\n'
    out += '\t\t};'

    return out


def main() -> None:
    pairs: list[list[str], list[str]] = [[], []]
    with open('macro-idents', 'r') as f:
        pairs[0] = f.readlines()
    with open('macro-vals', 'r') as f:
        pairs[1] = f.readlines()
    macros: dict[str, str] = dict()
    for macro, value in zip(pairs[0], pairs[1]):
        macros[macro[:-1] if macro[-1] == '\n' else macro] = value[:-1] if value[-1] == '\n' else value

    with open('constexprs.h', 'w') as f:
        f.write(generate_cpp(macros))


if __name__ == '__main__':
    main()
