const elem=340;  {folosim de la 1 la 340}
var s:longint;
    a:array[0..elem+5]of longint;
    i,h,b:longint;

function cauta(x:longint;var b:longint):boolean;
var i,j,m:longint;
begin
  cauta := false;
  i := 1; j := elem;
  repeat
    m := (i+j)div 2;
    if x <= a[m] then
      j := m-1
    else
      i := m+1;
  until i>j;
  if a[i] = x then
  begin
    cauta := true;
    b := i;
  end;
end;

begin
  assign(input,'dartz.in'); reset(input);
  assign(output,'dartz.out'); rewrite(output);

  readln(s); s := s div 2;

  for i := 1 to elem do
  begin
    h := i+1;
    a[i] := (h*h-1)*h;
  end;

  for i := 1 to elem  do
  begin
    if cauta(s-a[i],b) then
    begin
      writeln(i,' ',b,' ',i,' ',b);
      close(output);
      exit;
    end;

  end;


  close(input);
  close(output);
end.