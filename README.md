mac dylib bundler v2.2
======================


About
-----

**dylibbundler** is a macOS command-line utility for producing relocatable application bundles. External dependencies (dynamic libraries) are copied inside the app bundle, and install names are made run-path-relative. (https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/DynamicLibraries/100-Articles/RunpathDependentLibraries.html)


Installation
------------
In Terminal, from within the macdylibbundler directory:
```bash
mkdir build && cd build
cmake ..
make
```

To install in '/usr/local/bin':
```bash
sudo make install
```


Using dylibbundler
------------------
options:

`-h`, `--help`
<blockquote>
Displays a summary of options
</blockquote>

`-a`, `--app` (path to app bundle)
<blockquote>
Application bundle to make self-contained. Fixes the main executable of the app bundle. Add additional binary files to fix with the `-x` flag.
</blockquote>

`-x`, `--fix-file` (executable or plug-in filepath)
<blockquote>
Executable file or dynamic library (ex: .dylib, .so) to fix. Any file on which `otool -L` works is accepted by `-x`. dylibbundler will walk through the dependencies of the specified file to build a dependency list. It will also fix the said files' dependencies so that it expects to find the libraries relative to itself (e.g. in the app bundle) instead of at an absolute path (e.g. /usr/local/lib). To pass multiple files to fix, simply specify multiple `-x` flags.
</blockquote>

<!-- 
`-b`, `--bundle-deps`
<blockquote>
Copies libaries to a local directory, fixes their internal name so that they are aware of their new location,
fixes dependencies where bundled libraries depend on each other. If this option is not passed, no libraries will be prepared for distribution.
</blockquote>
 -->

`-f`, `--frameworks`
<blockquote>
Copy framework dependencies to app bundle and fix internal names and rpaths. If this option is not passed, dependencies contained in frameworks will be ignored. dylibbundler will also deploy Qt frameworks & plugins, eliminating the need to use `macdeployqt`.
</blockquote>

`-d`, `--dest-dir` (directory)
> Sets the name of the directory in wich distribution-ready dylibs will be placed, relative to `./MyApp.app/Contents`. (Default is `Frameworks`).

`-p`, `--install-path` (libraries install path)
> Sets the "inner" installation path of libraries, usually inside the bundle and relative to executable. (Default is `@executable_path/../Frameworks`, which points to a directory named `Frameworks` inside the `Contents` directory of the bundle.)

*The difference between `-d` and `-p` is that `-d` is the location dylibbundler will put files in, while `-p` is the location where the libraries will be expected to be found when you launch the app (often using @executable_path, @loader_path, or @rpath).*

`-s`, `--search-path` (search path)
> Check for libraries in the specified path.

`-i`, `--ignore` (path)
> Dylibs in (path) will be ignored. By default, dylibbundler will ignore libraries installed in `/usr/lib` & `/System/Library` since they are assumed to be present by default on all macOS installations. *(It is usually recommend not to install additional stuff in `/usr`, always use ` /usr/local` or another prefix to avoid confusion between system libs and libs you added yourself)*

`-of`, `--overwrite-files`
> When copying libraries to the output directory, allow overwriting files when one with the same name already exists.

`-cd`, `--create-dir`
> If the output directory does not exist, create it.

`-od`, `--overwrite-dir`
> If the output directory already exists, completely erase its current content before adding anything to it. (This option implies --create-dir)

`-n`, `--just-print`
> Print the dependencies found (without copying into app bundle).

`-q`, `--quiet`
> Less verbose output.

`-v`, `--verbose`
> More verbose output (only recommended for debugging).

`-V`, `--version`
> Print dylibbundler version number and exit.

A command may look like
`% dylibbundler -cd -of -f -q -a ./HelloWorld.app -x ./HelloWorld.app/Contents/PlugIns/printsupport`
