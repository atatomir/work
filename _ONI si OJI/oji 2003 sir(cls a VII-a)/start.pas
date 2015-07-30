var n:byte;
    a:array[1..3] of string[150];

procedure afla;
var i :byte;
    fo,f:text;

begin
  assign(f,'sir.in'); reset(f); read(f,n); close(f);
  assign(fo,'sir.out'); rewrite(fo);
  case n of
    1: write(fo,'a');
    2: write(fo,'b');
    else
    begin
      a[1]:= 'a'; a[2]:= 'b';

      for i := 3 to n do
      begin
        a[3] := a[2]+a[1];
        a[1]:= a[2];
        a[2]:= a[3];
      end;
    end;
  end;
  write(fo,a[3]);
  close(fo);
end;


begin
afla;
end.
