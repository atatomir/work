type pos = record
       i,v:longint;
     end;
var n,k,i,j,i1,i2,j1,j2,x,max:longint;
    bufin:array[1..65000]of byte;
    deq,deqq:array[1..1000000]of pos;

procedure add_deq(x:longint);
begin
  while j1 >= i1 do
  begin
    if deq[j1].v < x then break;
    dec(j1);
  end;

  inc(j1);
  deq[j1].v := x; deq[j1].i := j;

end;

procedure add_deqq(x:longint);
begin
  while j2 >= i2 do
  begin
    if deqq[j2].v > x then break;
    dec(j2);
  end;

  inc(j2);
  deqq[j2].v := x; deqq[j2].i := j;

end;

procedure verif();
begin
  while i > deq[i1].i do inc(i1);
  while i > deqq[i2].i do inc(i2);
end;

begin
  assign(input,'secvdist.in'); reset(input);
  assign(output,'secvdist.out'); rewrite(output);
  settextbuf(input,bufin);

  i1 := 1; i2 := 1; j1 := 0; j2 := 0; max := -1; i := 1;

  readln(n,k);

  for j := 1 to n do
  begin
    read(x);

    add_deq(x);
    add_deqq(x);

    while (deqq[i2].v - deq[i1].v > k) do
    begin
      inc(i);
      verif();
    end;

    if j-i+1 > max then max := j-i+1;
  end;

  writeln(max);


  close(input);
  close(output);
end.
