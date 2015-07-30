var n,i,h:longint;
    a:array[0..40]of int64;
    r:array[1..2,0..2000000]of int64;
    k,cont:int64;

procedure Rezolva(pas,h:longint;act:int64;compl:longint);
begin
  if pas <= h then
  begin
    Rezolva(pas+1,h,act,compl);
    Rezolva(pas+1,h,act+a[PAS],compl);
  end
  else
  begin
    inc(r[compl,0]);
    r[compl,r[compl,0]] := act;
  end;
end;

function cb(x:int64):int64;
var i,j,m:longint;
begin
  i := 1; j := r[2,0];
  repeat
    m := (i+j)div 2; //writeln(x,' ',r[2,m]);
    if r[2,m] >= x then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;

procedure QSort(dest,l,h:longint);
var i,j:longint;
    x,y:int64;
begin
  i := l; j := h; x := r[dest,(i+j)div 2];
  repeat
    while r[dest,i] < x do inc(i);
    while r[dest,j] > x do dec(j);
    if i <= j then
    begin
      y := r[dest,i]; r[dest,i] := r[dest,j]; r[dest,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(dest,l,j);
  iF i < h then QSort(dest,i,h);
end;

begin
  readln(n,k);
  for i := 1 to n do read(a[i]);
  cont := 0;

  h := n div 2;
  r[1,0] := 0; r[2,0] := 0;
  Rezolva(1,h,0,1);
  Rezolva(h+1,n,0,2);

  cont := 0;

  QSort(1,1,r[1,0]);
  QSort(2,1,r[2,0]);


  for i := 1 to r[1,0] do
  begin
    h := cb(k-r[1,i]);
    cont := cont + r[2,0] - h+1;
  end;

  writeln(cont);

end.
