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

begin
  assign(input,'datorii.in'); reset(input);
  assign(output,'datorii.out'); rewrite(output);
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
    readln(op,a,b);

    case op of
      0: add(a,-b);
      1: begin
           v1 := getsum(b);
           v2 := getsum(a-1);
           writeln(v1-v2);
         end;
    end;
  end;

  close(input);
  close(output);
end.
