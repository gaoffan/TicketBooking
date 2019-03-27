<template>
<div class="block">
  <el-card class="box-card input-card">
    <h3 class="t-c">车票查询</h3>
    <el-form ref="form" :model="form" label-width="80px">
    <el-form-item label="出发地" class="input">
      <el-input v-model="form.departure"></el-input>
    </el-form-item>
    <el-form-item label="到达地" class="input">
      <el-input v-model="form.arrival"></el-input>
    </el-form-item>
    <el-form-item label="出发日期">
      <el-date-picker v-model="form.departureDate" align="right" type="date" placeholder="请选择出发日期" :picker-options="pickerOptions1"></el-date-picker>
    </el-form-item>
    <div class="t-c">
      <el-button icon="el-icon-search" type="primary" @click="onSubmit()" round>查询</el-button>
    </div>
    </el-form>
  </el-card>
</div>
</template>

<script>
  export default {
    name: 'SearchCard',
    methods: {
      onSubmit () {
        this.$emit('search', this.form.departure, this.form.arrival, this.form.departureDate)
      }
    },
    data () {
      return {
        pickerOptions1: {
          disabledDate (time) {
            return time.getTime() < Date.now() - 3600 * 1000 * 24
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
          departureDate: new Date()
        }
      }
    }
  }
</script>

<style>
  .input{
    width: 300px;
  }
  .input-card{
    width: 400px;
  }
  .t-c {
    text-align: center
  }
</style>
