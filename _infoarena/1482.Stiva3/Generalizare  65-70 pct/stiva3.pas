var n,i,t,ant,pos,posaib,posant:longint;
    a,asort:array[0..50005]of longint;
    aib:array[0..50005]of longint;
    ok:boolean;
    bufin:array[1..65000]of byte;
 
function zeros(x:longint):longint;
begin
  zeros := (x and (x-1))xor x;
end;
 
 
procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := asort[(i+j)div 2];
  repeat
    while asort[i] < x do inc(i);
    while asort[j] > x do dec(j);
    if i <= j then
    begin
      y := asort[i]; asort[i] := asort[j]; asort[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;
 
procedure add(pos,v:longint);
begin
  while pos <= n do
  begin
    aib[pos] := aib[pos] + v;
    pos := pos + ((pos and (pos-1))xor pos);
  end;
end;
 
function sum(pos:longint):longint;
begin
  sum := 0;
  repeat
    sum := sum + aib[pos];
    pos := pos - ((pos and (pos-1))xor pos);
  until pos = 0;
end;
 
function cbsort(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n ;
  repeat
    m := (i+j) div 2;
    if x <= asort[m] then
      j := m-1
    else
      i := m+1;
  until i > j;
  cbsort := i;
end;
 
function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n ;
  repeat
    m := (i+j) div 2;
    if x <= sum(m) then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;
 
 
begin
  assign(input,'stiva3.in'); reset(input);
  assign(output,'stiva3.out'); rewrite(output);
  settextbuf(input,bufin);
 
  readln(n);
  for t := 1 to 5 do
  begin
    for i := 1 to n do
    begin
      read(a[i]);
      asort[i] := a[i];
      aib[i] := 0;
    end;
    QSort(1,n);
    for i := 1 to n do add(i,1);
 
    ant := 0; ok := true;
    for i := 1 to n do
    begin
      pos := cbsort(a[i]);
      if a[i] > ant then
      begin
        add(pos,-1);
      end
      else
      begin
        posant := cbsort(ant) ;
        posaib := cb(sum(posant));
        if asort[posaib] <> a[i] then
        begin
          ok := false;
          break;
        end
        else
        begin
          if (posant-posaib) <> (asort[posant]-asort[posaib]) then
          begin
            ok := false;
            break;
          end
          else
          begin
            add(pos,-1);
          end;
        end;
      end;
 
      ant := a[i];
    end;
 
    if ok then writeln(1) else writeln(0);
  end; readln();
 
 
 
 
  close(input);
  close(output);
end.