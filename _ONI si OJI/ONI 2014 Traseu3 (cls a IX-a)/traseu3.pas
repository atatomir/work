type poz = record
       x,y,z:byte;
     end;
var n,m,i,j,k,cont,val,x,y,z:longint;
    bg,en,pz:poz;
    a:array[0..105,0..105,0..105]of longint;
    c:array[0..1000005]of poz;
    bufin,bufout:array[1..65000]of byte;

procedure init();inline;
begin
  for i := 1 to n do
    for j := 1 to n do
      for k := 1 to n do
        a[i,j,k] := 0;

  for i := 1 to n do
    for j := 1 to n do
    begin
      a[0,i,j] := -1;
      a[n+1,i,j] := -1;
      a[i,0,j] := -1;
      a[i,n+1,j] := -1;
      a[i,j,0] := -1;
      a[i,j,n+1] := -1;
    end;
end;

procedure add_it(pz:poz;val:longint);inline;
begin
  inc(cont);
  c[cont] := pz;
  a[pz.x,pz.y,pz.z] := val;
end;

procedure add_its(x,y,z,val:longint);inline;
var pz:poz;
begin
  inc(cont);
  pz.x := x; pz.y := y; pz.z := z;
  c[cont] := pz;
  a[pz.x,pz.y,pz.z] := val;
end;

procedure add_nv(x,y,z:longint);inline;
var pz:poz;
begin
  inc(cont);
  pz.x := x; pz.y := y; pz.z := z;
  c[cont] := pz;
end;

function compare(a,b:poz):boolean;
begin
  compare := false;
  if a.x <> b.x then exit;
  if a.y <> b.y then exit;
  if a.z <> b.z then exit;
  compare := true;
end;

begin
  assign(input,'traseu3.in'); reset(input);
  assign(output,'traseu3.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m);
  init();

  readln(bg.x,bg.y,bg.z);
  readln(en.x,en.y,en.z);

  for i := 1 to m do
  begin
    readln(x,y,z);
    a[x,y,z] := -1;
  end;

  cont := 0;
  add_it(bg,1);

  i := 1;
  while i <= cont do
  begin
    pz := c[i]; inc(i);
    if Compare(pz,en) then break;
    x := pz.x; y := pz.y; z := pz.z;
    val := a[x,y,z];

    if a[x-1,y,z] = 0 then add_its(x-1,y,z,val+1);
    if a[x+1,y,z] = 0 then add_its(x+1,y,z,val+1);
    if a[x,y-1,z] = 0 then add_its(x,y-1,z,val+1);
    if a[x,y+1,z] = 0 then add_its(x,y+1,z,val+1);
    if a[x,y,z-1] = 0 then add_its(x,y,z-1,val+1);
    if a[x,y,z+1] = 0 then add_its(x,y,z+1,val+1);
  end;

  x := en.x; y := en.y; z := en.z;
  writeln(a[x,y,z]);

  cont := 0;
  repeat
    add_nv(x,y,z); val := a[x,y,z]-1;
    if a[x-1,y,z] = val then dec(x) else
    if a[x,y-1,z] = val then dec(y) else
    if a[x,y,z-1] = val then dec(z) else
    if a[x,y,z+1] = val then inc(z) else
    if a[x,y+1,z] = val then inc(y) else
    if a[x+1,y,z] = val then inc(x) ;
  until a[x,y,z] = 1;

  writeln(bg.x,' ',bg.y,' ',bg.z);
  for i := cont downto 1 do writeln(c[i].x,' ',c[i].y,' ',c[i].z);

  close(input);
  close(output);
end.