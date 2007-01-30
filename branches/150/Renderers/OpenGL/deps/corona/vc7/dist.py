PREFIX = ARGUMENTS.get('prefix', 'dist')

env = Environment(tools=[])
def install(target, source, files):
    from os.path import join
    from types import ListType

    if type(files) != ListType:
        files = [files]
    for f in files:
        env.Install(join(PREFIX, target), join(source, f))

# normal C++ interface
install('bin', 'vc7/Release', ['corona.dll'])
install('doc', 'doc',
        ['changelog.txt', 'code_guidelines.txt', 'dependencies.txt',
         'faq.txt', 'filetype-howto.txt', 'license.txt',
         'literature.txt', 'readme.txt', 'release-howto.txt',
         'tutorial.txt'])
install('include', 'src', 'corona.h')
install('lib', 'vc7/Release', 'corona.lib')
