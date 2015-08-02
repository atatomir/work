var n,m,i,op,x:longint;
    a:array[0..100005]of longint;
    bufin,bufout:array[1..65000]of byte;

function cb0(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;

  repeat
    m := (i+j)div 2;
    if x < a[m] then
      j := m-1
    else
      i := m+1;
  until i > j;
  if a[j] = x then cb0 := j else cb0 := -1;
end;

function cb1(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;

  repeat
    m := (i+j)div 2;
    if x < a[m] then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb1 := j;
end;

function cb2(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;

  repeat
    m := (i+j)div 2;
    if x <= a[m] then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb2 := i;
end;

begin
  assign(input,'cautbin.in'); reset(input);
  assign(output,'cautbin.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do read(a[i]);
  readln();
  readln(m);


  for i := 1 to m do
  begin
    readln(op,x);
    case op of
      0: writeln(cb0(x));
      1: writeln(cb1(x));
      2: writeln(cb2(x));
    end;

  end;




  close(input);
  close(output);
end.
