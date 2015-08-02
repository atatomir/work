uses crt;
var x:longword;
    s:longword;
    c:char;


begin
  clrscr;
  s:=0;
  writeln('/--------------------------------------------------------\');
  writeln('/Sabieri|Prastiasi|Arcasi|Hopliti|Calareti|Care|Catapulte\');
  writeln('/--------------------------------------------------------\');
  writeln('/       |         |      |       |        |    |         \');
  writeln('/--------------------------------------------------------\');
  writeln('/       |         |      |       |        |    |         \');
  writeln('/--------------------------------------------------------\');
  writeln('/------------------TOTAL:           ----------------------\');

  window(2,4,8,4);
  read(x);
  window(2,6,8,6);
  write(x);
  s:= s + x;

  window(10,4,18,4);
  read(x);
  window(10,6,18,6);
  write(x);
  s:= s + x;

  window(20,4,25,4);
  read(x);
  window(20,6,25,6);
  write(x);
  s:= s + x;

  window(27,4,33,4);
  read(x);
  window(27,6,33,6);
  write(x);
  s:= s + x;

  window(35,4,42,4);
  read(x);
  window(35,6,42,6);
  write(x*3);
  s:= s + x*3;

  window(44,4,47,4);
  read(x);
  window(44,6,47,6);
  write(x*4);
  s:= s + x*4;

  window(49,4,57,4);
  read(x);
  window(49,6,57,6);
  write(x*15);
  s:= s + x*15;

  window(26,8,36,8);
  write(s);
  c:= readkey;





end.
