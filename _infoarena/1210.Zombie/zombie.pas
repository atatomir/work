var d,n,k,i,t,tl,pos,cont:longint;
    cost:int64;
    bufin:array[1..65000]of byte;

begin
  assign(input,'zombie.in'); reset(input);
  assign(output,'zombie.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(d,n,k);
  cost := 0;

  read(t);   pos := 1;    cont := 1;

  for i := 2 to n do
  begin

    read(tl); //writeln('? ',tl,' ',t);
    tl := tl - t;
    pos := tl + pos;
    if pos <= d then
      inc(cont)
    else
    begin
      if cont < k then
        cost := cost + cont
      else
        cost := cost + k;
      //writeln(cont,'! ',cost,' ',i,' ',pos);

      pos := 1 ;
      cont := 1;
    end;
    t := t + tl;
  end;

  if cont < k then
    cost := cost + cont
  else
    cost := cost + k;

  write(cost);

  close(input);
  close(output);
end.
