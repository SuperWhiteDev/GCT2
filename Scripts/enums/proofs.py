class EntityProofs:
    def __init__(self, proof: int):
        self.bullet_proof = proof  & 1
        self.flame_proof = (proof >> 1) & 1
        self.explosion_proof = (proof >> 2) & 1
        self.collision_proof = (proof >> 3) & 1
        self.melee_proof = (proof >> 4) & 1
        self.steam_proof = (proof >> 5) & 1
        self.smoke_proof = (proof >> 6) & 1
        self.headshots_proof = (proof >> 7) & 1
        self.projectile_proof = (proof >> 8) & 1
    def get_proofs_bitset(self) -> int:
        proof = 0 
        proof |= self.bullet_proof
        proof |= self.flame_proof << 1
        proof |= self.explosion_proof << 2
        proof |= self.collision_proof << 3
        proof |= self.melee_proof << 4
        proof |= self.steam_proof << 5
        proof |= self.smoke_proof << 6
        proof |= self.headshots_proof << 7
        proof |= self.projectile_proof << 8
        return proof