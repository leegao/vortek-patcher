import lief
import sys, os

def main(libvortekrenderer):
    '''
    Design for hooking: in order to avoid having to change the dex code in order to intercept 
    VortekRendererComponent_createVkContext, we'll do the following instead:

    1. Rename VortekRendererComponent_createVkContext to old_VortekRendererComponent_createVkContext
    2. Have libvortekpatch.so export the original symbol (so that it gets called instead of libvortekrenderer)
    3. Add libvortekpatch.so as a DT_NEEDED library so it gets loaded with libvortekrenderer.so
    '''
    if not os.path.exists(libvortekrenderer):
        raise Exception(f"{libvortekrenderer} does not exist")

    if os.path.basename(libvortekrenderer) != "libvortekrenderer.so":
        raise Exception(f"{libvortekrenderer} must end with libvortekrenderer.so")

    binary = lief.parse(libvortekrenderer)

    for sym in binary.symbols:
        if sym.name == "Java_com_winlator_xenvironment_components_VortekRendererComponent_createVkContext":
            print(f"Patching {sym} to old_{sym.name}")
            sym.name = "old_" + sym.name
            break

    print("Adding libvortekpatch.so to DT_NEEDED")
    binary.add_library("libvortekpatch.so")
    binary.write(libvortekrenderer + ".new")

if __name__ == "__main__":
    main(sys.argv[1])
