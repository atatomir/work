type hack= record
       a,b:longint;
     end;

var n,i,nc:longint;
    h:array[1..50003]of hack;
    suma:int64;

begin
  assign(input,'hacker3.in');  reset(input);
  assign(output,'hacker3.out'); rewrite(output);

  readln(n);   suma := 0;               // citire jumatate
  nc := n div 2;
  for i := 1 to nc do readln();
  nc := (n+1) div 2;
  for i := nc downto 1 do readln(h[i].a,h[i].b);

                                             // parcurgere jumatate
  for i := 1 to nc do
  begin
    if suma + h[i].b > suma*2 + h[i].a then
      suma := suma*2 + h[i].a
    else
      suma := suma + h[i].b;
  end;

  close(input);
  assign(input,'hacker3.in'); reset(input);

  readln(n);  nc := n div 2;

  for i := nc downto 1 do        // citire cealalta jumatate
    readln(h[i].a,h[i].b);


  for i := 1 to nc do      //parcurgere cealalta jumatate
  begin
    if suma + h[i].b > suma*2 + h[i].a then
      suma := suma*2 + h[i].a
    else
      suma := suma + h[i].b;
  end;

  write(suma);


  close(input);
  close(output);
end.
