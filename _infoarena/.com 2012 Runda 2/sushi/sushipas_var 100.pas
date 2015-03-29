var bufin:array[1..65000]of byte;
    n,a,b,i,x,b1,b2,cont,cont2:longint;
    val,max:int64;
    ok:boolean;

begin
  assign(input,'sushi.in'); reset(input);
  assign(output,'sushi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); max := 0; ok := false;
  for i := 1 to n do
  begin
    read(x);
    if x > max then
    begin
      max := x;
      a := i;
      b:= i;
      ok := true;
      cont := 1;
    end
    else
    begin
      if x = max then
      begin
        if ok = true then
        begin
          b := i;
          inc(cont);
        end
        else
        begin
          inc(cont2);
        end;
      end
      else
      begin
        if x < max then
        begin
          ok := false;
          cont2 := 0;
        end;
      end;
    end;
  end;

  if cont2 > cont then cont := cont2;
  b1 := max; b2 := max;
  for i :=  2 to cont do
  begin
    b1 := b1 and max;
    b2 := b2 or max;
  end;

  val := b1 + b2;

  write(a,' ',b,' ',val);

  close(input);
  close(output);
end.
