include(`common.m4')

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
    <column style="padding: 0.5rem; max-width: 45rem; min-width: 45rem">

