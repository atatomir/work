const def=722563929;
type elem=record
       x,y,lung:longint;
     end;

var n,m,i,j,ccont,cont,start,max:longint;
    a:array[0..105,0..105]of char;
    v:array[1..5,1..2]of longint;
    r:array[1..5,1..5]of longint;
    c:array[0..10005]of elem;
    s:array[0..105,0..105]of longint;
    perm:array[1..5]of longint;

procedure add(i,j,x:longint);
begin
  inc(cont);
  c[cont].x := i; c[cont].y := j; c[cont].lung := x;
  s[i,j] := x;
end;

procedure renew;inline;
var i,j:longint;
begin
  for i := 1 to n do
    for j := 1 to m do
      s[i,j] := 0;
end;

procedure completeaza(sour,dest:longint); inline;
var i,j,bgi,bgj,val,rez:longint;
begin
  i := v[sour,1]; j := v[sour,2];
  bgi := v[dest,1]; bgj := v[dest,2];
  cont := 0;
  renew;
  add(i,j,0); start := 1;

  rez := -1;

  while start<=cont do
  begin
    i := c[start].x; j := c[start].y; val := c[start].lung; inc(start);

    if (i=bgi)and(j=bgj) then begin rez := val; break; end;

    if (a[i-1,j] <> '#')and(s[i-1,j] = 0) then add(i-1,j,val+1);
    if (a[i+1,j] <> '#')and(s[i+1,j] = 0) then add(i+1,j,val+1);
    if (a[i,j-1] <> '#')and(s[i,j-1] = 0) then add(i,j-1,val+1);
    if (a[i,j+1] <> '#')and(s[i,j+1] = 0) then add(i,j+1,val+1);
  end;

  r[sour,dest] := rez;  //WRITELN(SOUR,' ',DEST,' ',REZ);
  r[dest,sour] := rez;

end;

procedure permutare(pos:longint);
var i,j,sum:longint;
    exist:boolean;
begin
  if pos = ccont then
  begin
    perm[pos] := ccont;

    sum := 0;
    for i := 2 to ccont do
    begin
      if r[perm[i-1],perm[i]] <> -1 then
      begin
        sum := (sum + r[perm[i-1],perm[i]]);
      end
      else
        exit;
    end;
    if sum < max then max := sum;
  end
  else
  begin
    for i := 2 to ccont-1 do
    begin
      exist := false;
      for j := 2 to pos-1 do
        if perm[j] = i then exist := true;

      if not exist then
      begin
        perm[pos] := i;
        permutare(pos+1);
        perm[pos] := 0;
      end;
    end;
  end;
end;

procedure bording();inline;
var i:longint;
begin
  for i := 0 to n do
  begin
    s[i,0] := -1;
    s[i,m+1] := -1;
  end;
  for i := 0 to m do
  begin
    s[0,i] := -1;
    s[n+1,i] := -1;
  end;
end;

begin
  readln(n,m); ccont := 0;
  bording;  max := def;

  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]);
      if a[i,j] = 'S' then begin v[1,1] :=i; v[1,2] := j; end;
      if a[i,j] = 'D' then begin inc(ccont); v[ccont+1,1] := i; v[ccont+1,2] := j; end;
      if a[i,j] = 'B' then begin v[5,1] :=i; v[5,2] := j; end;
    end;
    readln();
  end;
  v[ccont+2,1] := v[5,1]; v[ccont+2,2] := v[5,2]; inc(ccont,2);

  for i := 1 to ccont-1 do
    for j := i+1 to ccont do
    begin
      completeaza(i,j);
    end;

  perm[1] := 1; perm[2] := 0; perm[3] := 0; perm[4] := 0; perm[5] := 0;
  permutare(2);

  if max = def then max := -1;
  writeln(max);
end.
