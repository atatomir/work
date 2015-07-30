type atlet=record
       d:longint;
       v:real;
     end;
     nodh=record
       v:double;
       pos,dest:longint;
     end;
var n,l,i:longint;
    a:array[0..500005]of atlet;
    ap:array[0..500005]of boolean;

    h:array[-1..500005]of nodh;
    pos:array[0..500005]of longint;
    cont,sour,dest:longint;

function p(x:longint):longint; begin p := x div 2; end;
function c1(x:longint):longint; begin c1 := x*2; end;
function c2(x:longint):longint; begin c2 := x*2+1; end;

procedure up(nod:longint);inline;
var par:longint;
    y:nodh;
begin
  repeat
    par := p(nod);
    if h[par].v > h[nod].v then
    begin
      y := h[par]; h[par] := h[nod]; h[nod] := y;
      pos[h[nod].pos] := nod;
      pos[h[par].pos] := par;
      nod := par;
    end
    else
      break;
  until 1 = 0;
end;

procedure down(nod:longint);inline;
var ch1,ch2:longint;
    y:nodh;
begin
  repeat
    ch1 := c1(nod);
    ch2 := c2(nod);
    if ch1 > cont then ch1 := -1;
    if ch2 > cont then ch2 := -1;

    if h[ch1].v > h[ch2].v then ch1 := ch2;
    if h[nod].v > h[ch1].v  then
    begin
      y := h[ch1]; h[ch1] := h[nod]; h[nod] := y;
      pos[h[ch1].pos] := ch1;
      pos[h[nod].pos] := nod;
      nod := ch1;
    end
    else
      break;
  until 1 = 0;
end;

procedure del_h(x:longint);inline;
begin
  h[x] := h[cont]; dec(cont);
  pos[h[x].pos] := x;
  up(x);
  down(x);
end;


procedure add_h(x:longint);inline;
var i,next,d:longint;
    v:double;
begin
  next := -1; pos[x] := -1;

  for i := x+1 to n do
    if ap[i] then
    begin
      next := i;
      break;
    end;
  if next = -1 then
  for i := 1 to x-1 do
    if ap[i] then
    begin
      next := i;
      break;
    end;

  if next <> -1 then
    if a[x].v > a[next].v then
    begin
      v := a[x].v - a[next].v;
      if x < next then d := a[next].d-a[x].d else d := l - a[x].d + a[next].d;

      inc(cont);
      pos[x] := cont;
      h[cont].v := d/v;
      h[cont].pos := x;
      h[cont].dest := next;
      up(cont);

      //for i := 1 to cont do write(h[i].v:0:2,' '); writeln();
    end;

end;


begin
  {assign(input,'cyc.in'); reset(input);
  assign(output,'cyc.out'); rewrite(output);   }

  readln(n,l);
  for i := 1 to n do
  begin
    readln(a[i].d,a[i].v);
    ap[i] := true;
  end;

  h[0].v := -1; h[-1].v := 9999999999999;

  for i := 1 to n do add_h(i);

  while cont > 0 do
  begin
    sour := h[1].pos; dest := h[1].dest;
    del_h(1);
    ap[dest] := false; writeln(dest);
    if pos[dest] <> -1 then del_h(pos[dest]);
    pos[dest] := -1;
    add_h(sour);
  end;

  write('Winner(s): ');
  for i := 1 to n do
    if ap[i] then
      write(i,' ');

  {close(input);
  close(output);  }
end.