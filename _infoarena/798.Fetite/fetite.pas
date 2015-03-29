var n,p:int64;


begin
  assign(input,'fetite.in'); reset(input);
  assign(output,'fetite.out'); rewrite(output);

  readln(n);

  p := 1 ;
  while p*2 <= n do p := p*2;

  write((n-p)*2+1);


  close(input);
  close(output);
end.