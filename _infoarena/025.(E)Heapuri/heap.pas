type nodh=record
       v,pos:longint;
     end;
var n,i,cont,op,x,contop1:longint;
    heap:array[-1..200005]of nodh;
    pos:array[0..200005]of longint;
    bufin,bufout:array[1..65000]of byte;

function p(x:longint):longint; begin p := x div 2; end;
function c1(x:longint):longint; begin c1 := x*2; end;
function c2(x:longint):longint; begin c2 := x*2+1; end;

procedure up(nod:longint);inline;
var par:longint;
    y:nodh;
begin
  repeat
    par := p(nod);

    if heap[nod].v < heap[par].v then
    begin
      pos[heap[nod].pos] := par; pos[heap[par].pos] := nod;
      y := heap[nod]; heap[nod] := heap[par]; heap[par] := y;
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

    if (heap[nod].v > heap[ch1].v)or(heap[nod].v > heap[ch2].v) then
    begin
      if heap[ch2].v < heap[ch1].v then ch1 := ch2;
      pos[heap[nod].pos] := ch1; pos[heap[ch1].pos] := nod;
      y := heap[nod]; heap[nod] := heap[ch1]; heap[ch1] := y;
      nod := ch1;
    end
    else
      break;
  until 1 = 0;
end;

procedure add(x:longint);inline;
begin
  inc(cont); inc(contop1);
  heap[cont].v := x; heap[cont].pos := contop1;
  pos[contop1] := contop1;

  up(cont);
end;

procedure del(x:longint);inline;
begin
  x := pos[x];
  if x = cont then
    dec(cont)
  else
  begin
    heap[x] := heap[cont];
    pos[heap[cont].pos] := x;
    dec(cont);

    up(x);
    down(x);
  end;
end;

begin
  assign(input,'heapuri.in'); reset(input);
  assign(output,'heapuri.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n); contop1 := 0;
  cont := 0; heap[0].v := -1; heap[-1].v := 1000000005;

  for i := 1 to n do
  begin
    read(op);
    case op of
      1: begin read(x); add(x); end;
      2: begin read(x); del(x); end;
      3: writeln(heap[1].v);
    end;

    //write('! '); for x := 1 to cont do write(heap[x].v,' '); writeln();
  end;


  close(input);
  close(output);
end.