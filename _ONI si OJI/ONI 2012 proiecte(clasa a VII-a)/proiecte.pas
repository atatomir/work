var n,m,i,j,c,ant,apar,proj,max:longint;
    a:array[1..201]of longint;
    v:array[1..200001]of longint;
    //bufin:array[1..65000]of byte;
    iesi:boolean;
    fo:text;

procedure major(x:longint);
begin
  if apar = 0 then
  begin
    apar := 1;
    ant := x;
  end
  else
  begin
    if x = ant then
      inc(apar)
    else
      dec(apar);
  end;
end;

function vermajor(x:longint):boolean;
var cont,i:longint;
begin
  vermajor := false;
  cont := 0;
  for i := 1 to c do
    if v[i] = x then inc(cont);
  if cont > c div 2 then vermajor := true;
end;

procedure Sort;
var i,t:longint;
begin
  repeat
    iesi := true;
    for i := 1 to proj-1 do
      if a[i] > a[i+1] then
      begin
        t := a[i];
        a[i] := a[i+1];
        a[i+1] := t;
        iesi := false;
      end;
  until iesi = true;
end;

procedure afla_max ;
var maxl,maxp,i:longint;
begin
  max := 0;
  maxl := 1; maxp := a[1] ;
  for i := 2 to proj do
  begin
    if a[i] = maxp then
      inc(maxl)
    else
    begin
      if max < maxl then max := maxl;
      maxl := 1;
      maxp := a[i];
    end;
  end;

  if max < maxl then max := maxl;

end;

procedure scrie_max;
var i,maxl,maxp:longint;
begin
  maxp := a[1]; maxl := 1;
  for i := 2 to proj do
  begin
    if a[i] = maxp then
      inc(maxl)
    else
    begin
      if maxl = max then write(fo,maxp,' ');
      maxl := 1; maxp := a[i];
    end;
  end;

  if maxl = max then write(fo,maxp);

end;

begin
  assign(input,'proiecte.in'); reset(input);
  assign(fo,'proiecte.out'); rewrite(fo);

  readln(n,m);      proj := 0;            writeln('test1');
  for i := 1 to m do
  begin
    read(c);  read(v[1]); ant := v[1]; apar := 1;
    for j := 2 to c do
    begin
      read(v[j]);
      major(v[j]);
    end;

    if apar > 0 then
      if vermajor(ant) then
      begin
        inc(proj);
        a[proj] := ant;
      end;

  end;

  Sort;         writeln('test4');
  afla_max;     writeln('test5');
  scrie_max;    writeln('test6');


  close(input);       writeln('test7');
  close(fo);
end.
