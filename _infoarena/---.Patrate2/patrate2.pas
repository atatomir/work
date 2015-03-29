var n,i,cs,c0,cd,s,d,t,h:longint;
    nr:array[0..2,0..700000]of longint;
    help:array[1..30]of longint;

procedure inmulteste(x:longint);inline;
var i,j:longint;
begin
   c0 := 0;
   while x <> 0 do
   begin
     inc(c0);
     nr[0,c0] := x mod 100;
     x := x div 100;
   end;
   for i := 1 to c0+cs+5 do nr[d,i] := 0;
   cd := c0+cs-1;

   for i := 1 to c0 do
     for j := 1 to cs do
     begin
       nr[d,i+j-1] := nr[d,i+j-1] + nr[0,i]*nr[s,j];
     end;

   for i := 2 to cd do
   begin
     nr[d,i] := nr[d,i] + (nr[d,i-1] div 100);
     nr[d,i-1] := nr[d,i-1] mod 100;
   end;

   if nr[d,cd] > 100 then
   begin
     nr[d,cd+1] := nr[d,cd] div 100;
     nr[d,cd] := nr[d,cd] mod 100;
     inc(cd);
   end;

   cs := cd;
   t := s; s := d; d := t;
end;

begin
  assign(input,'patrate2.in'); reset(input);
  assign(output,'patrate2.out'); rewrite(output);

  readln(n);
  s := 1; d := 2;
  cs := 1; nr[s,1] := 1;

  help[1] := 2;
  for i := 2 to 30 do help[i] := help[i-1]*2;

  for i := 2 to n do inmulteste(i);
  h := n*n;
  while h <> 0 do
  begin
    if h <= 30 then
    begin
      inmulteste(help[h]);
      h := 0;
    end
    else
    begin
      inmulteste(help[30]);
      h := h - 30;
    end;
  end;

  for i := cs downto 1 do
  begin
    if (nr[s,i] < 10)and(i <> cs) then write(0);
    write(nr[s,i]);
  end;

  close(input);
  close(output);
end.
