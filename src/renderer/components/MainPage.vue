<template>
  <el-row>
  <el-col :span="12">
  <el-card class="box-card">
    <el-form ref="form" :model="form" label-width="80px">
    <el-form-item label="出发地" required>
      <el-input v-model="form.departure"></el-input>
    </el-form-item>
    <el-form-item label="到达地" required>
      <el-input v-model="form.arrival"></el-input>
    </el-form-item>
    <el-form-item label="出发日期" prop="date1" required>
      <el-date-picker v-model="form.departureDate" align="right" type="date" placeholder="请选择出发日期" :picker-options="pickerOptions1"></el-date-picker>
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="onSubmit()">查询</el-button>
    </el-form-item>
    </el-form>
  </el-card>
      <div class="grid-content bg-purple">
      <div class="block">
      
      </div>
      </div>
    </el-col>
    <el-col :span="12"><div class="grid-content bg-purple-light"></div></el-col>
  </el-row>
</template>

<script>
  export default {
    name: 'main-page',
    methods: {
      open (link) {
        this.$electron.shell.openExternal(link)
      },
      onSubmit () {
        alert('submit!')
      }
    },
    data () {
      return {
        pickerOptions1: {
          disabledDate (time) {
            return time.getTime() > Date.now()
          },
          shortcuts: [{
            text: '今天',
            onClick (picker) {
              picker.$emit('pick', new Date())
            }
          }, {
            text: '明天',
            onClick (picker) {
              const date = new Date()
              date.setTime(date.getTime() + 3600 * 1000 * 24)
              picker.$emit('pick', date)
            }
          }, {
            text: '一周后',
            onClick (picker) {
              const date = new Date()
              date.setTime(date.getTime() + 3600 * 1000 * 24 * 7)
              picker.$emit('pick', date)
            }
          }]
        },
        form: {
          departure: '',
          arrival: '',
          departureDate: ''
        }
      }
    }
  }
</script>

<style>
  
</style>
