var n,i:longint;
    iesi: boolean;
    p,r:real;

begin
  assign(input,'pitagora2.in'); reset(input);
  assign(output,'pitagora2.out'); rewrite(output);

  readln(n);  i := n;  iesi := false; r := -1;

  repeat
    inc(i);
    p := i*i-n*n;
    if trunc(sqrt(p))*trunc(sqrt(p)) = p then
    begin
      r := sqrt(p);
      iesi := true;
    end;
  until iesi = true;

  write(trunc(r));


  close(input);
  close(output);
end.