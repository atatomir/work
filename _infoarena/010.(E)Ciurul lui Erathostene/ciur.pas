var n,i,cont,h,h2,j:longint;
    a:array[2..2000001]of boolean;

begin
  assign(input,'ciur.in'); reset(input);
  assign(output,'ciur.out'); rewrite(output);

  read(n);  cont := 0;
  for i := 2 to n do a[i] := true;

  h := trunc(sqrt(n))+1 ;
  for i := 2 to h do
  begin
    if a[i]= true then
    begin
      h2 := (n div i) ;
      for j := 2 to h2 do
        a[j*i] := false;
    end;
  end;

  for i := 2 to n do
    if a[i] = true then inc(cont);

  write(cont);

  close(input);
  close(output);
end.

//      /---------\         /\
//      |   o o   |        /  \
//      |    ^    |       / o o\
//      |  \___/  |      /   _  \
//      \---------/     /________\