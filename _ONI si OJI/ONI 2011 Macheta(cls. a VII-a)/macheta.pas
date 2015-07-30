var n,i,hi,j,k:longint;
    h:array[0..2001,0..2001]of longint;
    nr:array[0..2001,0..2001]of longint;    //
    bufin,bufout:array[1..65000]of byte;
    x,y,lx,ly:longint;   //
    apar:array[1..1001]of boolean;

begin
  assign(input,'macheta.in'); reset(input);
  assign(output,'macheta.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  for i := 1 to 2000 do
    for j := 1 to 2000 do
    begin
      h[i,j] := -10;
      nr[i,j] := 0;
    end;

  readln(n); //citire
  for i := 1 to n do
  begin
    readln(x,y,lx,ly,hi);
    for j := y to y + ly -1 do
    begin
      for k := x to x + lx -1 do
      begin
        h[j,k] := hi;
        nr[j,k] := i;
      end;
    end;
  end;              //terminare citire

  {for i := 0 to 10  do  //debug
  begin
    for j  := 0 to 10 do
      write(nr[i,j],' ');
    writeln();
  end;       }

  for i := 1 to n do apar[i] := false;  //initializare vector apar


  for i := 1 to 2000 do
  begin
    hi := -5;
    for j := 1 to 2000 do
    begin
                              //writeln(i,' ',j,' ',hi,' ',h[j,i]);
      if h[j,i] > hi then
      begin
        hi := h[j,i];
        apar[nr[j,i]] := true;
      end;
   end;
  end;


  for i := 1 to 100 do
    if apar[i] = true then write(i,' ');

  close(input);
  close(output);
end.
