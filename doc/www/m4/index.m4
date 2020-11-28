include(`header.m4')

<section style="text-align: center">
  <img style="width: 18rem" src="images/logo_large.png">
</section>

<section>
_title(`Welcome to the Iffe UI Toolkit')

Iffe is a UI library for the C programming language. It aims to keep
things simple and fun. It was born out of frustration of current UI
systems which are often too heavy in terms of dependencies, they lack in
portability and maintenance or they are too awkward to use, relying on
multiple diseperate layout scripts resulting in poor workflow or requiring
too much boiler-plate code for tasks that should be trivial. Iffe has
a number of project aims, including:

<ul>
  <li style="margin: 0.5rem 0">

_bold(`C89+') ensures that the code is kept simple and maximizes portability. Even
to older platforms.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Object-oriented via MACROs') helps to organise the project in a
way that many developers would expect.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Minimize dependencies') ensures that the code remains light,
portable and easy to build and maintain.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Focus on maintainability') reduces bitrot and ensures that we
can rely on this software for many years to come.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Single static library') helps avoid versioning issues and prevents
package managers from making a mess.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Provide simple layout system') and avoid tooling ensures that
building UIs remains fast and fun.

  </li>
  <li style="margin: 0.5rem 0">

_bold(`Memory testing in debug builds') allows you to focus on developing
great software rather than spending your time finding bugs.

  </li>
</ul>

Check out the tutorial page to get started using Iffe and to see some
of these concepts put into practice.

</section>

<dark_section>

_bold(`Note:') Please keep in mind that Iffe is still in the very early
stages of development. Don't expect it to provide replacements of a
number of useful UI components quite yet. However due to the nature of
Iffe, many of these should be easy to implement and any contributions
are greatly appreciated!

</dark_section>

<note_section>
_title(`Introducing the Flow Layout System')

Iffe takes a new approach to layout management. Whereas traditional
systems usually rely on a grid based layout (i.e CSS FlexBox, JGridBag,
VBox/HBox) or anchoring (i.e Winforms, Motif), this alternative approach
(called Flow) intends to solve a number of these inherent issues. For
example:

<ul>
  <li style="margin: 0.5rem 0">

No tooling should be required, instead the layout can be defined
separately from the logic but in the same homogenous C language as the
rest of the software. There really is no need for external XML or JSON
files when C can serve the task in a simpler way.

  </li>
  <li style="margin: 0.5rem 0">

Future maintenance should be simple. No need to maintain old build
systems just to support a specific preprocessor should be needed. Instead
a standards compliant C compiler should be all that is necessary.

  </li>
  <li style="margin: 0.5rem 0">

Revisiting previous projects and adding new layout should be kept
simple. No need to be overwhelmed by complex nested hierarchies. Flow
should be quick to follow and natural to implement.

  </li>
</ul>

Check out the flow tutorial for more information and then take a look at some of the examples.
</note_section>

<section>
_title(`Introducing the Stent Memory Checker (libstent)')

Looking at the C programming language from a platform point of view,
it certainly has some benefits such as great performance, reduced
dependencies and fantastic lifespan ranging from ancient platforms such
as supporting early UNIX and MS/PC-DOS all the way to modern, mobile and
experimental platforms. Even new platforms coming out today still see C
as a first class citizen. However as a programming language it has a few
potential limitations. One of the most crucial is its manual approach
to memory management. Whilst this has many useful applications, it can
often make it too easy for a developer to make mistakes and add hard
to find memory related bugs to their program. These typically manifest
themselves as use-after-free, dangling pointers or uninitialized variable
errors. The Stent memory checker intends to solve this by providing the
following features:

<ul>
  <li style="margin: 0.5rem 0">

100% checked heap usage in debug builds ensures that the program
aborts with useful information about the mistake immediately and in a
deterministic manner.

  </li>
  <li style="margin: 0.5rem 0">

Typesafe weak pointer in the debug build (similar to C++
std::weak_ptr&lt;T&gt;). Once testing has been done, this can be stripped
in the release build ensuring there is zero additional overhead.

  </li>
  <li style="margin: 0.5rem 0">

Typesafe dynamic arrays (similar to C++ std::vector&lt;T&gt;). In both
the debug and release builds this container greatly simplifies memory
access in heap arrays and eliminates a range of programming mistakes.

  </li>
  <li style="margin: 0.5rem 0">

Leak checker in the debug build notifies the programmer upon exit of any
allocations which were not subsequently freed along with their type and
location in code where they were allocated.

  </li>
  <li style="margin: 0.5rem 0">

100% portable C89+. No need for a specific compiler or platform. For
example, no reliance on address sanitation support in your compiler or
the ability to lock virtual memory.

  </li>
</ul>

Stent is built-in and deeply integrated with Iffe. However it is also
encouraged that it is used for many C projects, even those entirely
unrelated to UI. Of course Iffe can also be used without the memory
checker. In this case standard raw pointers can be used as normal.

Check out the Stent tutorial for detailed information on how it works. All
the examples also use Stent but if you want to use Iffe directly without
it, you can check out this specific example here.

</section>

include(`footer.m4')

