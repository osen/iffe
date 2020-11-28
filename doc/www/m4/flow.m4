define(`_TITLE', `Flow')
include(`header.m4')

<section>
_title1(`The Flow Layout System')

Iffe implements a unique layout system called Flow which works in a
largely different manner to existing systems you may have encountered
so far.  However it is intended to simplify the UI development process
and provide a much smoother workflow for both initial development as
well as future maintenance. For now, lets have a look at how it works
and what kinds of functionality it provides.

<br><br>

The first step is to create a minimal program displaying a single window
with a button. This can be done using the following code:

_code(`
  #include &lt;iffe/iffe.h&gt;

  widget(MainWindow, Init)
  {
    int dummy; /* We have no members yet! */
  };

  void OnInit(struct InitEvent *ev)
  {
    ref(Widget) button = WidgetAdd(ev->sender, Button);
  }
')

This is an entire program and Iffe does not require you to create a
main function. Instead any Widget given the name MainWindow will be
initialized and displayed as a top-level window. The program can be
compiled as a normal C program using a command similar to:

_code(`
  $ cc -oflow main.c -liffe -lX11
')

This would result in a window appearing with the following layout.

_image(`images/flow/1_button_initial.png')

You will notice that by default the button will appear at the bottom
right corner of the window if no positional instructions are given. This
may seem strange at first (i.e other systems default to the top left)
however after you start to use the system you may start to see that it
offers a few conveniences.

<br><br>

Our next step is to move the button to the top left. Rather than set
absolute coordinates (such as 0, 0), Flow works using instructions. So
as the window is resized, these same instructions get rerun and the
window layout is regenerated (albeit at a different size). For now we
just move up via the following code:

_code(`
  WidgetFlow(button, "^");
')

As you may have guessed, directions are given within the WidgetFlow
function via &lt; &gt; ^ v symbols.  As the following image demonstrates,
the button will keep moving upwards until it hits either the edge of
the window or another positioned Widget.

_image(`images/flow/2_button_up.png')

With that in place, we can then instruct the Widget to move to the
left. Rather than writing multiple statements in C, the command can be
collapsed as seen in the following code:

_code(`
  WidgetFlow(button, "^<");
')

So with this, the button will first move all the way to the top edge,
and then all the way to the left edge as shown in the following:

_image(`images/flow/3_button_up_left.png')

With this in place, we will now create a new Text Box and provide it the
same instructions to move up and left. This will place it neatly beside
the original button. You will see that if we swap the instructions and
move it left first and then up, it will result in being placed under the
original button. This provides useful flexibility. The code for the Text
Box should be as follows.

_code(`
  ref(Widget) text = WidgetAdd(ev->sender, TextBox);
  WidgetFlow(text, "^<");
')

The following image shows the route that the Text Box will take. This
should also be fairly easy to visualize compared to other approaches
using many nested grid containers.

_image(`images/flow/4_text_up_left.png')

Next we are going to add a Separator Widget to close off the top row. For
this we are going to do something slightly different. Instead of moving to
the left, we provide an instruction for the Widget to expand left. this
means it will keep growing towards the left until it touches the left
edge. After this our usual instruction to move upwards is given.

_code(`
  ref(Widget) sep = WidgetAdd(ev->sender, Separator);
  WidgetFlow(text, "=<^");
')

So again, you may notice that any directional instruction with a =
symbol before it will expand in that direction rather than simply move.
This process is demonstrated by the following image.

_image(`images/flow/5_separator_expand_left_up.png')

Note that the Separator Widget is by default 1x1 pixels in size. This
allows us to expand it in the vertical direction as well as
horizontal. The final result of this can be seen in the following image.

_image(`images/flow/6_separator_result.png')
_image(`images/flow/7_textarea_expand_1.png')
_image(`images/flow/8_textarea_expand_2.png')
_image(`images/flow/9_textarea_expand_result.png')
_image(`images/flow/10_resize.png')

</section>

include(`footer.m4')

