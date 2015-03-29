const modd = 1000007;
      base = 17;
var n,nn,i,per:longint;
    s:ansistring;
    bufin:array[0..65000]of byte;

function verif(l:longint):boolean;
var ind,h,bg,en:int64;
    i,j:longint;
begin
  verif := true;

  h := n div l;
  for i := 2 to h do
  begin
    bg := l*(i-1)+1; en := l*i;  ind := 0;

    for j := bg to en do
    begin
      inc(ind);
      if s[j] <> s[ind] then
      begin
        verif := false;
        break;
      end;
    end;
    if not verif then break;
  end;
end;

function nr_div(x:longint):int64;
var i,h:longint;
    p:int64;
begin
  nr_div := 1;
  h := trunc(sqrt(x))+1;
  for i := 2 to h do
  begin
    p := 0;
    while x mod i = 0 do
    begin
      inc(p);
      x := x div i;
    end;
    inc(p);
    nr_div := nr_div * p;
  end;
  if x <> 1 then nr_div := nr_div * 2;
end;

begin
  assign(input,'perioada2.in'); reset(input);
  assign(output,'perioada2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);

  per := -1; nn := n div 2;
  for i := 1 to nn do
    if n mod i = 0 then
      if verif(i) then
      begin
        per := i;
        break;
      end;

  if per = -1 then
    writeln(0)
  else
  begin
    n := n div per;
    writeln(nr_div(n)-1);
  end;

  close(input);
  close(output);
end.
