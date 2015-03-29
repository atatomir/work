var aib:array[0..100005]of longint;
    n,m,i,x,op,a,b,v1,v2,h:longint;
    bufin:array[1..65000]of byte;

function zeros(x:longint):longint;
begin
  zeros := (x xor (x-1))and x;
end;

procedure add(pos,v:longint); inline;
begin
  repeat
    aib[pos] := aib[pos] + v;
    pos := pos + zeros(pos);
  until pos >  n;
end;

function getsum(pos:longint):longint;
begin
  getsum := 0; if pos = 0 then exit;
  repeat
    getsum := getsum + aib[pos] ;
    pos := pos - zeros(pos);
  until pos <= 0;
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if x <= getsum(m) then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;

begin
  assign(input,'aib.in'); reset(input);
  assign(output,'aib.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to n do aib[i] := 0;

  for i := 1 to n do
  begin
    read(x);
    add(i,x);
  end;  readln();

  for i := 1 to m do
  begin
    read(op,a);
    if op < 2 then read(b);
    readln();

    case op of
      0: add(a,b);
      1: begin
           v1 := getsum(b);
           v2 := getsum(a-1);
           writeln(v1-v2);
         end;
      2: begin
           h := cb(a);
           if getsum(h) <> a then
             writeln(-1)
           else
             writeln(h);
         end;
    end;

  end;



  close(input);
  close(output);
end.