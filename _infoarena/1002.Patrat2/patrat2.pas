var bufout:array[1..65000]of byte;
    n,i:longint;

begin
  assign(input,'patrat2.in'); reset(input);
  assign(output,'patrat2.out'); rewrite(output);
  settextbuf(output,bufout);

  read(n);

  while n<> 0 do
  begin
    i := trunc(sqrt(n));
    writeln(i);
    n := n - i*i;
  end;
  close(input);
  close(output);
end.