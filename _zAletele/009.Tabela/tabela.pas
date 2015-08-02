var n,m:longint;
begin
  assign(input,'tabela.in'); reset(input);
  assign(output,'tabela.out'); rewrite(output);

  readln(n,m);
  writeln((n-1) xor (m-1));


  close(input);
  close(output);
end.