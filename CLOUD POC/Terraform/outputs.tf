output "kubeconfig" {
  value = ovh_cloud_project_kube.cluster.kubeconfig
  sensitive = true
}

output  "username_opsk" {
  value = ovh_cloud_project_user.user1.username
}

output  "password_opsk" {
  value = ovh_cloud_project_user.user1.password
  sensitive = true
}

output  "rc_opsk" {
  value = ovh_cloud_project_user.user1.openstack_rc
}