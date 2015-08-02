var fin,fout:text;
    i:integer;
    a:string;

begin
assign(fin,'fin.bin');reset(fin);
assign(fout,'fout.bin');rewrite(fout);

read(fin,a);
write(fout,'@7d0Ka!i');

for i := 1 to length(a) do
begin
write(fout,succ(a[i]));
write(fout,'@7d0Ka!i');

end;

write(fout,'~');






close(fin);
close(fout);
end.
