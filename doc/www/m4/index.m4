Welcome to the Iffe UI Toolkit

Iffe is a UI library for the C programming language. It aims to keep things simple and fun. It was born out of frustration of current UI systems which are often too heavy in terms of dependencies, they lack in portability and maintenance or they are too awkward to use, relying on multiple diseperate layout scripts resulting in poor workflow or requiring too much boiler-plate code for tasks that should be trivial. Iffe has a number of project aims, including:

- C89+ ensures that the code is kept simple and maximizes portability. Even to older platforms.
- Object-oriented via MACROs helps to organise the project in a way that many developers would expect.
- Minimize dependencies ensures that the code remains light, portable and easy to build and maintain.
- Focus on maintainability reduces bitrot and ensures that we can rely on this software for many years to come.
- Single static library helps avoid versioning issues and prevents package managers from making a mess.
- Provide simple layout system and avoid tooling ensures that building UIs remains fast and fun.
- Memory testing in debug builds allows you to focus on developing great software rather than spending your time finding bugs.

Introducing the Flow Layout System

Iffe takes a new approach to layout management. Whereas traditional systems usually rely on a grid based layout (i.e CSS FlexBox, JGridBag, VBox/HBox) or anchoring (i.e Winforms, Motif), this alternative approach (called Flow) intends to solve a number of these inherent issues. For example:

- No tooling should be required, instead the layout can be defined separately from the logic but in the same homogenous C language as the rest of the software. There really is no need for external XML or JSON files when C can serve the task in a simpler way.

- Future maintenance should be simple. No need to maintain old build systems just to support a specific preprocessor should be needed. Instead a standards compliant C compiler should be all that is necessary.

- Revisiting previous projects and adding new layout should be kept simple. No need to be overwhelmed by complex nested hierarchies. Flow should be quick to follow and natural to implement.

Check out the flow tutorial for more information and then take a look at some of the examples.

Introducing the Stent Memory Checker (libstent)

Looking at the C programming language from a platform point of view, it certainly has some benefits such as great performance, reduced dependencies and fantastic lifespan ranging from ancient platforms such as supporting early UNIX and MS/PC-DOS all the way to modern, mobile and experimental platforms. Even new platforms coming out today still see C as a first class citizen. However as a programming language it has a few potential limitations. One of the most crucial is its manual approach to memory management. Whilst this has many useful applications, it can often make it too easy for a developer to make mistakes and add hard to find memory related bugs to their program. These typically manifest themselves as use-after-free, dangling pointers or uninitialized variable errors. The Stent memory checker intends to solve this by providing the following features:

- 100% checked heap usage in debug builds ensures that the program aborts with useful information about the mistake immediately and in a deterministic manner.

- Typesafe weak pointer in the debug build (similar to C++ std::weak_ptr<T>). Once testing has been done, this can be stripped in the release build ensuring there is zero additional overhead.

- Typesafe dynamic arrays (similar to C++ std::vector<T>). In both the debug and release builds this container greatly simplifies memory access in heap arrays and eliminates a range of programming mistakes.

- Leak checker in the debug build notifies the programmer upon exit of any allocations which were not subsequently freed along with their type and location in code where they were allocated.

- 100% portable C89+. No need for a specific compiler or platform. For example, no reliance on address sanitation support in your compiler or the ability to lock virtual memory.

Stent is built-in and deeply integrated with Iffe. However it is also encouraged that it is used for many C projects, even those entirely unrelated to UI. Of course Iffe can also be used without the memory checker. In this case standard raw pointers can be used as normal.

Check out the Stent tutorial for detailed information on how it works. All the examples also use Stent but if you want to use Iffe directly without it, you can check out this specific example here.