program bete;
var f,g:text;
    a:array[1..1000] of integer;
    b:array[1..1000] of integer;
    n,i:longint;
begin
        assign(f, 'bete.in');
        assign(g, 'bete.out');
        reset(f);
        rewrite(g);
        for i:=1 to n do
                begin
                readln(f,a[i]);
                readln(f,b[i]);
                end;
        close(f);
        close(g);
end.
