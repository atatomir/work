const mod1 = 1000000007;

var n,i:longint;
    a:array[1..100001]of int64;
    s:array[1..100001]of int64;
    bufin:array[1..65000]of byte;
    suma:int64;

procedure Sort(l, r: int64);
var
  i, j, x, y: int64;
begin
  i := l; j := r; x := a[(l+r) DIV 2];
  repeat
    while a[i] < x do i := i + 1;
    while x < a[j] do j := j - 1;
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;

begin
  assign(input,'galagie.in'); reset(input);
  assign(output,'galagie.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do readln(a[i]);
  Sort(1,n);

  s[1] := a[1];
  for i := 2 to n-1 do s[i] := (s[i-1] + a[i])mod mod1;

  suma := 0;

  for i := 1 to n-1 do
  begin
    suma := (suma -s[i]+(i*a[i+1]) mod mod1  )mod mod1;
  end;

  write((2*suma)mod mod1);

  close(input);
  close(output);
end.
