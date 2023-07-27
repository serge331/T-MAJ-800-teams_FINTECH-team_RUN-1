# AWX

## Approle
- Custom vault_token creds pointe vers un credential approle
- Création de vault_token pour chaque environnement pointant vers les policies correspondantes
- Double sécurité: AppRole sur un path spécifique avec un token limitant l'accès aux ressources. 