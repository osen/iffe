<!DOCTYPE html>
<html>
  <head>
    <title>Home - Iffe UI Library</title>
    <style>

body
{
  display: flex;
  margin: 0%;
}

img
{
  border: none;
}

body::before
{
  content: '';
  height: 100vh;
  visibility: hidden;
}

column
{
  //border: 1px solid red;
  display: flex;
  flex-direction: column;
  flex-basis: 0%;
  flex-grow: 1;
}

row
{
  //border: 1px solid blue;
  display: flex;
  flex-direction: row;
  flex-basis: 0%;
  flex-grow: 1;
}

spacer
{
  //border: 1px solid orange;
  flex-basis: 0%;
  flex-grow: 1;
}

.collapse
{
  //border: 1px solid green;
  flex-basis: auto;
  flex-grow: 0;
}

section
{
  //border: 1px solid black;
  padding: 1rem;
  margin: 0.5rem;
  background: white;
}

dark_section
{
  //border: 1px solid black;
  padding: 1rem;
  margin: 0.5rem;

  color: white;
  background-image: url('images/noise_background.png');
  background-repeat: repeat;
}

note_section
{
  border: 1px solid black;
  padding: 1rem;
  margin: 0.5rem;

  color: white;
  background: maroon;
}

note_title
{
  display: block;
  font-weight: bold;
  padding-bottom: 0.5rem;
  text-decoration: underline;
}

#sidebar
{
  background-image: url('images/texture.png');
  background-repeat: repeat;
  //background: maroon; 
}

#sidebar a:link,
#sidebar a:visited
{
  font-size: 16pt;
  text-decoration: none;
  color: white;
}

#sidebar a:hover
{
  text-decoration: underline;
}

#sidebar a:active
{
  color: gray;
}

    </style>
  </head>
  <body>
    <column id="sidebar" class="collapse" style="padding: 0.5rem; border-right: 1px solid black">
      <img src="images/logo.png" style="width: 150px">
      <spacer style="max-height: 15vh"></spacer>
      <column class="collapse" style="text-align: center">
        <div><a href="#">Home</a></div>
        <div><a href="#">Download</a></div>
        <div><a href="#">Documentation</a></div>
        <div><a href="#">Tutorials</a></div>
        <div><a href="#">Contact</a></div>
      </column>
      <spacer style="border-bottom: 1px solid black"></spacer>
      <label style="padding-top: 0.5rem; text-align: center; color: white; font-size: 12pt">
Copyright &copy; 2020<br>Iffe Project
      </label>
    </column>
    <spacer></spacer>
    <column style="padding: 0.5rem; max-width: 40rem; min-width: 40rem">
      <section style="text-align: center">
        <img style="width: 18rem" src="images/logo_large.png">
      </section>
      <section>

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer consequat
mollis blandit. Sed eget nisl at neque ultricies lacinia. Donec interdum,
nibh nec ornare maximus, ipsum urna tincidunt metus, id pellentesque mi
leo vel ipsum. Donec faucibus libero quis diam semper, vitae condimentum
diam egestas. In cursus ultrices suscipit. Vivamus facilisis, dolor sed
tristique mollis, nisl tellus vehicula augue, hendrerit luctus ex turpis
eget turpis. Pellentesque habitant morbi tristique senectus et netus
et malesuada fames ac turpis egestas. Nulla laoreet quam sit amet nibh
pretium, in imperdiet mi volutpat. Pellentesque malesuada lacus ac lorem
porttitor placerat. Praesent egestas elit in porttitor facilisis. Duis
vitae odio fermentum, lacinia est vel, accumsan sem. Nunc ac tellus
neque. Nunc nec ultricies nisl, ut malesuada ipsum.
      </section>
      <dark_section>
Curabitur id tincidunt libero. Etiam ante lacus, euismod maximus est sit
amet, placerat dictum urna. Aliquam pharetra diam vitae velit facilisis
auctor. Donec a eleifend urna, vel tempus est. Integer ipsum ante,
sollicitudin vel orci vel, scelerisque pellentesque nunc. Maecenas a ipsum
in magna lobortis aliquam. Nulla sed metus aliquet, viverra lectus sit
amet, condimentum erat. Morbi tincidunt massa in convallis gravida. Nam
at elit sed metus dapibus bibendum. Mauris tempor dolor id augue iaculis,
sit amet fermentum est aliquam.
      </dark_section>
      <section>
Duis feugiat sodales orci et pretium. Morbi vel tincidunt mauris. In
tincidunt dolor ut tempor lacinia. Praesent fermentum ullamcorper
facilisis. Pellentesque ullamcorper, enim a pellentesque elementum, purus
est ultricies ipsum, id pellentesque nulla magna non libero. Quisque nec
euismod turpis, posuere egestas urna. Aliquam erat volutpat. Suspendisse
varius mi non dui placerat egestas. Vestibulum non tortor bibendum,
malesuada nunc ac, pellentesque ante. Suspendisse potenti. Etiam a urna
nisi. Sed dictum tellus vitae arcu efficitur malesuada. Cras sit amet arcu
urna. In vitae libero sit amet neque finibus mollis non at tortor. Aenean
sed magna fermentum, blandit enim vel, dictum ante. Curabitur sit amet
urna non dui rhoncus dapibus at sit amet nibh.
      </section>
      <note_section>
        <div style="font-weight: bold; padding-bottom: 0.5rem; text-decoration: underline"><label>Note</label></div>
Curabitur dapibus ligula sit amet pharetra euismod. Quisque faucibus
tincidunt nulla vel pulvinar. Aliquam porta mi pharetra congue
venenatis. Suspendisse ullamcorper sapien eros, quis tincidunt leo
tempus porta. Vestibulum ligula nisl, accumsan sit amet convallis ac,
luctus eget nunc. Mauris mattis ligula id ultrices commodo. Suspendisse
ut dolor facilisis, viverra lorem in, eleifend justo. Aliquam porttitor
placerat libero. Sed eget est eu ex sodales finibus. Integer consequat
blandit diam a euismod. Nam velit tortor, aliquet rhoncus nisi vel,
auctor luctus dolor. Donec rutrum id sem a tincidunt. Mauris faucibus,
augue et tincidunt lacinia, neque felis blandit ligula, non fermentum
dui lorem sed mi. Ut finibus a lacus at fringilla. Fusce ut sollicitudin
lacus. Sed posuere tempus neque at condimentum.
      </note_section>
      <section>
Nunc vestibulum at quam ac iaculis. In hac habitasse platea dictumst. Nam
fringilla pellentesque ligula, in condimentum tellus sagittis vitae. Orci
varius natoque penatibus et magnis dis parturient montes, nascetur
ridiculus mus. Aenean interdum euismod purus. Nunc nec pretium mi. Etiam
ac hendrerit magna. Curabitur purus massa, porta ultrices hendrerit vel,
sodales non dolor. Ut iaculis eros felis, vel facilisis nibh lacinia
sed. Donec quis justo velit. Suspendisse consectetur orci ligula.
      </section>
    </column>
    <spacer></spacer>
  </body>
</html>

