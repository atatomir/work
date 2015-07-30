const luna:array[0..12]of byte = (0,31,28,31,30,31,30,31,31,30,31,30,31);
var bufin:array[1..65000]of byte;
    t,ti,i:longint;
    l,z,h,m,s:array[1..2]of byte;
    a:array[-5..86400]of longint;
    palim:longint;

function verif(x:longint):boolean;
var r1,r2:longint;
begin
  r1 := x; r2 := 0;
  while x <> 0 do
  begin
    r2 := r2*10 + x mod 10;
    x := x div 10;
  end;
  if r1=r2 then verif := true else verif := false;
end;

procedure do_array;
var h,m,s:byte;
    i,ant:longint;
begin
  h := 0; m := 0; s := 0;
  for i := 0 to 86400 do a[i] := 0;

  for i := 1 to 86400 do
  begin
    m := m + (s div 60); s := s mod 60;
    h := h + (m div 60); m := m mod 60;

    if verif(h*10000+m*100+s) then a[i-1] := 1;

    inc(s);
  end;

  ant := a[0];
  for i := 1 to 86399 do
  begin
    ant := ant + a[i];
    a[i] := ant;
  end;

end;

procedure add_rest(l1,z1,l2,z2:longint);
begin
  if  z2 = 0 then
  begin
    dec(l2);
    z2 := luna[l2];
  end;

  while not((l1=l2)and(z1=z2)) do
  begin

    if z1 = luna[l1] then
    begin
      z1 := 1;
      inc(l1);
    end;

    palim := palim + a[86399];
    inc(z1);

  end;


end;


begin
  assign(input,'momente.in'); reset(input);
  assign(output,'momente.out'); rewrite(output);
  settextbuf(input,bufin);

  do_array;  a[-1] := 0;

  readln(t);
  for ti := 1 to t do
  begin
    readln(l[1],z[1],h[1],m[1],s[1],l[2],z[2],h[2],m[2],s[2]);
    palim := 0;

    if (l[1] = l[2])and(z[1] = z[2]) then
      palim := a[h[2]*3600+m[2]*60+s[2]] - a[h[1]*3600+m[1]*60+s[1]-1]
    else
    begin
      palim := a[86399] - a[h[1]*3600+m[1]*60+s[1]-1];
      palim := palim + a[h[2]*3600+m[2]*60+s[2]];

      add_rest(l[1],z[1]+1,l[2],z[2]-1);
    end;


    writeln(palim);

  end;

  close(input);
  close(output);
end.
