type nodh=record
       v,id:longint;
     end;
     taskit=record
       a,b:longint;
     end;

var n,m,k,i,time,pos:longint;
    aib:array[0..100005]of longint;
    bufin,bufout:array[1..65000]of byte;
    task:array[0..100005]of taskit;

    h:array[-1..100005]of nodh;
    cont:longint;

function zeros(x:longint):longint; begin zeros := (x xor(x-1))and x; end;
function p(x:longint):longint; begin p := x div 2; end;
function c1(x:longint):longint; begin c1 := 2*x; end;
function c2(x:longint):longint; begin c2 := 2*x+1; end;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:taskit;
begin
  i := l; j := h; x := task[(i+j)div 2].a;
  repeat
    while task[i].a < x do inc(i);
    while task[j].a > x do dec(j);
    if i <= j then
    begin
      y := task[i]; task[i] := task[j]; task[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

procedure up(nod:longint); inline;
var y:nodh;
    par:longint;
begin
  repeat
    par := p(nod);
    if h[nod].v < h[par].v then
    begin
      y := h[nod]; h[nod] := h[par]; h[par] := y;
      nod := par;
    end
    else
      break;
  until 1 = 0;
end;

procedure down(nod:longint); inline;
var ch1,ch2:longint;
    y:nodh;
begin
  repeat
    ch1 := c1(nod);
    ch2 := c2(nod);
    if ch1 > cont then ch1 := -1;
    if ch2 > cont then ch2 := -1;

    if (h[nod].v > h[ch1].v)or(h[nod].v > h[ch2].v) then
    begin
      if h[ch1].v > h[ch2].v then ch1 := ch2;
      y := h[nod]; h[nod] := h[ch1]; h[ch1] := y;
      nod := ch1;
    end
    else
      break;
  until 0 = 1;
end;

procedure add_aib(x,val:longint); inline;
begin
  while x <= n do
  begin
    inc(aib[x],val);
    x := x + zeros(x);
  end;
end;

procedure add_h(x,id:longint); inline;
begin
  inc(cont);
  h[cont].v := x; h[cont].id := id;
  up(cont);
end;

procedure del_h(x:longint); inline;
begin
  h[x] := h[cont]; dec(cont);
  up(x);
  down(x);
end;

procedure update(limit:longint);inline;
begin
  while cont > 0 do
  begin
    if h[1].v > limit then
      break
    else
    begin
      add_aib(h[1].id,1);
      del_h(1);
    end;
  end;
end;

function sum_aib(x:longint):longint;
var sum:longint;
begin
  sum := 0;
  repeat
    sum := sum + aib[x];
    x := x - zeros(x);
  until x = 0;
  sum_aib := sum;
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if x <= sum_aib(m) then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;

begin
  assign(input,'muncitori.in'); reset(input);
  assign(output,'muncitori.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m,k);
  for i := 1 to n do aib[i] := 0;
  for i := 1 to n do add_aib(i,1);

  time := 0; cont := 0;
  h[0].v := -1;
  h[-1].v := 2000005;

  for i := 1 to m do readln(task[i].a,task[i].b);
  QSort(1,m);

  for i := 1 to m do
  begin
    update(task[i].a);
    pos := cb(k);
    add_aib(pos,-1);
    writeln(pos);
    add_h(task[i].a+task[i].b,pos)
  end;

  close(input);
  close(output);
end.