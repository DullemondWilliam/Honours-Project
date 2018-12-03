
$$
Set(A) = Set(elements\:unique\:to\:A) + Set(elements\:shared\:with\:B)\\
Set(B) = Set(elements\:unique\:to\:B) + Set(elements\:shared\:with\:A)\\
Set(A) = Set(u_a) + Set(s) \:\:\:\:\:\:\:\: Set(B) = Set(u_b) + Set(s)\\
N_a = |Set(A)|\:\:\:\:\:\:\:\:\: N_b = |Set(B)|
$$



$$
Pr(not\: set\:by\:S)*Pr(not\: set\: by\: U_b)*Pr(set\:by\:U_A)=Pr(only\:set\:by U_1)\\

(1-(1/m))^{k|s|} * (1-(1/m))^{k(n_b-|s|)} * (1-(1-(1/m)^{k|u_a|}))=x\\

((m-1)/m)^{k|s|} * ((m-1)/m)^{k(n_b-|s|)} * (1-((m-1)/m)^{k|u_a|})=x\\

((m-1)/m)^{kn_b} * (1-((m-1)/m)^{k|u_a|})=x\\

u = (log(((m - 1)/m)^{(k* n_b)} - x) - k*n*log((m - 1)/m))/(k*log((m - 1)/m))
$$






